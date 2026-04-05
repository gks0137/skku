num_str = input("숫자를 입력하시오:\n")

ones_place = int(num_str[-1])

if ones_place != 0 and ones_place % 3 == 0:
    print("Yes")
else:
    print("No")