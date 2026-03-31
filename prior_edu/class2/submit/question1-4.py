sum = 0
while True:
    num = input("숫자를 입력하시오:")
    if num == '0':
        break
    sum += int(num)

print(sum)