import math
for _ in range(int(input())):
    n = int(input())
    ans = int(math.sqrt(n))
    while ans * ans + ans > n:
        ans -= 1
    print(ans)
    