"""Hold-out validation of the baseline on the training period.

Trains the baseline model on the `--train-years` years before `--valid-start`,
forecasts [valid-start, valid-end] from the training-period day-ahead weather
forecasts, and scores it against train/generation.parquet with scoring.py.

    python validate.py                                  # 2024-06 ~ 2025-05 hold-out
    python validate.py --valid-start "2023-06-01 01:00" --valid-end "2024-06-01 00:00"
"""
from __future__ import annotations
import argparse
import numpy as np
import pandas as pd
import lightgbm as lgb

from baseline import HERE, ROUNDS, WA_COLS, WB_COLS, FEATS, features, log
from scoring import score

KST = "Asia/Seoul"


def main() -> None:
    ap = argparse.ArgumentParser(description="baseline hold-out validation")
    ap.add_argument("--valid-start", default="2024-06-01 01:00")
    ap.add_argument("--valid-end", default="2025-06-01 00:00")
    ap.add_argument("--train-years", type=float, default=2.0)
    ap.add_argument("--composition", default=f"{HERE}/composition.csv")
    ap.add_argument("--min-coverage", type=float, default=0.95)
    ap.add_argument("--out", default=f"{HERE}/val_forecast.csv")
    args = ap.parse_args()

    v0 = pd.Timestamp(args.valid_start, tz=KST)
    v1 = pd.Timestamp(args.valid_end, tz=KST)
    t0 = v0 - pd.Timedelta(days=round(365.25 * args.train_years))
    log(f"train {t0:%Y-%m-%d} ~ {v0:%Y-%m-%d}  /  valid {v0} ~ {v1}")

    sites = pd.read_csv(f"{HERE}/sites.csv")[
        ["site_id", "current_group", "capacity_kw", "lat", "lon",
         "wa_station", "wb_station"]]

    gen = pd.read_parquet(f"{HERE}/train/generation.parquet")
    gen["ts"] = pd.to_datetime(gen.ts)
    fa = pd.read_parquet(f"{HERE}/train/forecast_wa.parquet",
                         columns=["wa_station", "round", "ts"] + WA_COLS)
    fb = pd.read_parquet(f"{HERE}/train/forecast_wb.parquet",
                         columns=["wb_station", "round", "ts"] + WB_COLS)
    for d in (fa, fb):
        d["ts"] = pd.to_datetime(d.ts)

    gen_tr = gen[(gen.ts >= t0) & (gen.ts < v0)]
    log(f"train generation {len(gen_tr):,} rows")

    # same model as baseline.py, fit only on data before the hold-out window
    models = {}
    for r in ROUNDS:
        d = features(gen_tr, sites, fa, fb, None, r)
        d = d[d.elev > 0]
        y = (d.energy / d.cap).clip(0, 1.2).astype("float32")
        X = d[FEATS].astype("float32")
        models[r] = lgb.LGBMRegressor(
            n_estimators=600, learning_rate=0.06, num_leaves=127,
            min_child_samples=200, subsample=0.8, subsample_freq=1,
            colsample_bytree=0.8, verbose=-1, n_jobs=-1).fit(X, y)
        log(f"round={r} trained on {X.shape}")
        del d, X, y

    comp = pd.read_csv(args.composition)
    grp = comp.set_index("site_id").group
    index = pd.date_range(v0, v1, freq="h")
    out = []
    for r in ROUNDS:
        d = features(None, sites, fa, fb, index, r)
        p = np.where(d.elev.to_numpy() > 0,
                     models[r].predict(d[FEATS].astype("float32")), 0.0)
        d["kwh"] = np.clip(p, 0, None) * d.cap.to_numpy()
        d["group"] = d.site_id.map(grp)
        out.append(d.groupby(["group", "ts"], as_index=False).kwh.sum())
        log(f"round={r} predicted")

    f = (pd.concat(out).groupby(["group", "ts"], as_index=False).kwh.mean()
           .rename(columns={"kwh": "forecast_kwh"}).sort_values(["group", "ts"]))
    f.to_csv(args.out, index=False)
    log(f"saved {args.out} ({len(f):,} rows)")

    smp = pd.read_csv(f"{HERE}/train/smp.csv")
    smp["ts"] = pd.to_datetime(smp.ts).dt.tz_convert(KST)
    r = score(comp, f, gen, smp, min_coverage=args.min_coverage)
    print(f"\nperiod   {r['period'][0]} ~ {r['period'][1]}  ({r['hours']:,} h)")
    print(f"rows     scored {r['rows_scored']:,} / dropped {r['rows_dropped']:,} "
          f"(coverage < {args.min_coverage})")
    print(f"revenue  {r['revenue']:>18,.0f}")
    print(f"penalty  {r['penalty']:>18,.0f}  ({r['penalty_ratio']:.2%} of revenue)")
    print(f"S        {r['S']:>18,.0f}")
    print(r["by_group"].map(lambda v: f"{v:,.0f}").to_string())


if __name__ == "__main__":
    main()
