n = int(input("숫자를 입력하시오:"))

sum = 0
for power in range(n+1):
    sum += 2 ** power

print(f"2^0부터 2^{n} 까지의 합은 {sum}입니다.")