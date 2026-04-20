j, n = map(int, input().split())
ans = 0
for _ in range(n):
    line = input()
    number = 0
    for c in line:
        if c == '\n' :
            break
        if c == ' ':
            number += 1
        elif c.isupper():
            number += 4
        else:
            number += 2
    
    if number <= j:
        ans += 1
    #print(number)
print(ans)