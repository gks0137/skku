num_str = input("숫자를 입력하시오:")

sum = 0
for num in num_str:
    sum += int(num)

print(f"{num_str}의 자릿수의 합은 {sum}입니다.")