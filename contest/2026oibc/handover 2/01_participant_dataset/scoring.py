"""OIBC 2026 score calculator.

    S = Σ SMP(t)·actual(t)  −  0.10 × Σ SMP(t)·k(t)·|forecast(t) − actual(t)|

summed over both groups (G1, G2) and every scored hour. k = 3 when the hour of
ts is 11~15, else 1.

The test period has no actual generation, so this scores against the training
period (train/generation.parquet) — use it on a hold-out validation window:

    python scoring.py --composition comp.csv --forecast val_forecast.csv
    python scoring.py ... --start "2024-06-01 01:00" --end "2025-06-01 00:00"

In Python:
    from scoring import score
    res = score(comp_df, forecast_df, generation_df, smp_df)

Missing actuals: generation.parquet has no row when a site did not report.
Hours where a group's reporting capacity share is below --min-coverage are
dropped (otherwise a correct forecast would be penalised for missing data).
"""
from __future__ import annotations
import argparse, os
import numpy as np
import pandas as pd

HERE = os.path.dirname(os.path.abspath(__file__))
PENALTY = 0.10
MIN_GROUP_KW = 20_000


def k_weight(ts: pd.Series) -> np.ndarray:
    h = pd.DatetimeIndex(ts).hour
    return np.where((h >= 11) & (h <= 15), 3, 1)


def check_composition(comp: pd.DataFrame, sites: pd.DataFrame) -> pd.DataFrame:
    """Validate the submission rules; returns comp merged with capacity."""
    assert set(comp.columns) >= {"site_id", "group"}, "composition needs site_id, group"
    assert comp.site_id.is_unique, "duplicate site_id in composition"
    missing = set(sites.site_id) - set(comp.site_id)
    extra = set(comp.site_id) - set(sites.site_id)
    assert not missing and not extra, f"site mismatch: missing={sorted(missing)[:5]} extra={sorted(extra)[:5]}"
    assert comp.group.isin(["G1", "G2"]).all(), "group must be G1 or G2"
    c = comp.merge(sites[["site_id", "capacity_kw"]], on="site_id")
    cap = c.groupby("group").capacity_kw.sum()
    for g in ("G1", "G2"):
        assert cap.get(g, 0) >= MIN_GROUP_KW, f"{g} capacity {cap.get(g, 0):,.1f} kW < {MIN_GROUP_KW:,} kW"
    return c


def group_actuals(comp: pd.DataFrame, gen: pd.DataFrame) -> pd.DataFrame:
    """Per (group, ts): summed actual kWh and share of group capacity that reported."""
    d = gen.merge(comp, on="site_id", how="inner")
    a = d.groupby(["group", "ts"]).agg(actual_kwh=("energy", "sum"),
                                       rep_kw=("capacity_kw", "sum")).reset_index()
    a["coverage"] = a.rep_kw / a.group.map(comp.groupby("group").capacity_kw.sum())
    return a.drop(columns="rep_kw")


def score(comp: pd.DataFrame, forecast: pd.DataFrame, gen: pd.DataFrame,
          smp: pd.DataFrame, sites: pd.DataFrame | None = None,
          min_coverage: float = 0.95) -> dict:
    """Compute S. All ts columns must be tz-aware datetimes."""
    if sites is None:
        sites = pd.read_csv(f"{HERE}/sites.csv")
    comp = check_composition(comp, sites)

    f = forecast[["group", "ts", "forecast_kwh"]].copy()
    assert not f.duplicated(["group", "ts"]).any(), "duplicate (group, ts) in forecast"
    assert (f.forecast_kwh >= 0).all() and f.forecast_kwh.notna().all(), "forecast_kwh must be >= 0"

    s = smp[["ts", "smp"]].copy()
    s["k"] = smp["k"] if "k" in smp else k_weight(smp.ts)

    a = group_actuals(comp, gen)
    d = f.merge(s, on="ts", how="inner").merge(a, on=["group", "ts"], how="left")
    n_total = len(d)
    d = d[d.coverage >= min_coverage]          # drops hours with no/insufficient actuals
    if d.empty:
        raise ValueError("no scorable hours — check that forecast ts overlaps generation/smp")

    d["revenue"] = d.smp * d.actual_kwh
    d["penalty"] = PENALTY * d.smp * d.k * (d.forecast_kwh - d.actual_kwh).abs()
    d["score"] = d.revenue - d.penalty

    by_group = d.groupby("group")[["revenue", "penalty", "score"]].sum()
    hours = d.ts.nunique()
    return {
        "S": d.score.sum(),
        "revenue": d.revenue.sum(),
        "penalty": d.penalty.sum(),
        "penalty_ratio": d.penalty.sum() / d.revenue.sum(),   # lower is better
        "by_group": by_group,
        "rows_scored": len(d), "rows_dropped": n_total - len(d), "hours": hours,
        "period": (d.ts.min(), d.ts.max()),
        "detail": d,
    }


def _read_ts(path: str) -> pd.DataFrame:
    df = pd.read_parquet(path) if path.endswith(".parquet") else pd.read_csv(path)
    df["ts"] = pd.to_datetime(df.ts)
    if df.ts.dt.tz is None:
        raise ValueError(f"{path}: ts must be timezone-aware")
    df["ts"] = df.ts.dt.tz_convert("Asia/Seoul")
    return df


def main() -> None:
    ap = argparse.ArgumentParser(description="OIBC 2026 score calculator")
    ap.add_argument("--composition", default=f"{HERE}/composition.csv")
    ap.add_argument("--forecast", default=f"{HERE}/forecast.csv")
    ap.add_argument("--generation", default=f"{HERE}/train/generation.parquet")
    ap.add_argument("--smp", default=f"{HERE}/train/smp.csv")
    ap.add_argument("--start", default=None, help="first ts to score (KST)")
    ap.add_argument("--end", default=None, help="last ts to score (KST)")
    ap.add_argument("--min-coverage", type=float, default=0.95,
                    help="min share of group capacity with reported actuals")
    ap.add_argument("--detail-out", default=None, help="save hourly breakdown to csv")
    args = ap.parse_args()

    comp = pd.read_csv(args.composition)
    fc, gen, smp = _read_ts(args.forecast), _read_ts(args.generation), _read_ts(args.smp)
    for name in ("start", "end"):
        v = getattr(args, name)
        if v:
            t = pd.Timestamp(v)
            t = t.tz_localize("Asia/Seoul") if t.tzinfo is None else t
            fc = fc[fc.ts >= t] if name == "start" else fc[fc.ts <= t]

    r = score(comp, fc, gen, smp, min_coverage=args.min_coverage)
    print(f"period   {r['period'][0]} ~ {r['period'][1]}  ({r['hours']:,} h)")
    print(f"rows     scored {r['rows_scored']:,} / dropped {r['rows_dropped']:,} "
          f"(coverage < {args.min_coverage})")
    print(f"revenue  {r['revenue']:>18,.0f}")
    print(f"penalty  {r['penalty']:>18,.0f}  ({r['penalty_ratio']:.2%} of revenue)")
    print(f"S        {r['S']:>18,.0f}")
    print(r["by_group"].map(lambda v: f"{v:,.0f}").to_string())
    if args.detail_out:
        r["detail"].to_csv(args.detail_out, index=False)


if __name__ == "__main__":
    main()
