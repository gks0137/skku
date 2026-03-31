calc = input("식을 입력하세요: ").split("-")

for i, parts in enumerate(calc):
    calc[i] = sum(map(int, parts.split("+")))

minimum = calc[0]
for minus in calc[1:]:
    minimum -= minus

print('최솟값은 %d 입니다.' % (minimum))