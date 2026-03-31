rockpaperscissor = ['바위', '보', '가위']

p1 = int(input("첫 번째 사람을 입력하시오: "))
p2 = int(input("두 번째 사람을 입력하시오: "))

print("첫 번째 사람:", rockpaperscissor[p1])
print("두 번째 사람:", rockpaperscissor[p2])

if p1 == p2:
    print("비겼습니다.")
elif (p1 +1) % 3 == p2:
    print("두 번째 사람이 이겼습니다.")
else:
    print("첫 번째 사람이 이겼습니다.")








