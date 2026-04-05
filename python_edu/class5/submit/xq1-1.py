N = input()

howmany1 = 0

if len(N) == 1:
    print(1 if int(N) >= 1 else 0)
    exit()

for n, nth_place in enumerate(N):
    howmany1 += int(N[:n] + '0' * len(N[n+1:]))
    if int(nth_place) > 1:
        howmany1 += int('1' + '0' * len(N[n+1:]))
    elif int(nth_place) == 1:
        howmany1 += int('0' + N[n+1:]) + 1

print(howmany1)