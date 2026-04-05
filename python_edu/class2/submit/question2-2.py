x, y = map(int, input("2차원 공간의 좌표 (x, y)를 입력하세요: ").split())

quadrant = None
if x > 0 and y > 0:
    quadrant = 1
elif x < 0 and y > 0:
    quadrant = 2
elif x < 0 and y < 0:
    quadrant = 3
elif x > 0 and y < 0:
    quadrant = 4

def is_in_quadrant(num):
    if num == quadrant:
        print(f"({x}, {y})는 제{num}사분면에 속합니다.")
    else:
        print(f"({x}, {y})는 제{num}사분면에 속하지 않습니다.")

for rep in range(1, 5):
    is_in_quadrant(rep)
