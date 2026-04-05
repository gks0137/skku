#조건 연산자 ? 가 뭐인지 모르겠습니다...
#인터넷에 찾아보니 java에서는 해당 문법이 존재하는데, 삼항 연산자(conditional operator)라고 하더군요.
#파이썬 문법으로 삼항 연산자를 써서 만들어 보았습니다.

x1, y1, x2, y2 = map(int, input("첫 번째 2차원 공간의 두 점 (x1, y1), (x2, y2)를 입력하세요: ").split())
x3, y3, x4, y4 = map(int, input("두 번째 2차원 공간의 두 점 (x3, y3), (x4, y4)를 입력하세요: ").split())


print(f"(x1, y1), (x2, y2)의 값은 ({x1}, {y1}), ({x2}, {y2})")
print(f"(x3, y3), (x4, y4)의 값은 ({x3}, {y3}), ({x4}, {y4})")


#두 직선이 일치하는 경우도 있는데, 결과 화면 예시를 보니 일치하는 경우에도 평행하다고 출력하는 것 같아서 그렇게 처리했습니다.

deg_a = (y2 - y1) / (x2 - x1)
deg_b = (y4 - y3) / (x4 - x3)
is_parallel = True if deg_a == deg_b else False

print("두 직선은 평행합니다.") if is_parallel else print("두 직선은 평행하지 않습니다.")





#is_parallel = (x1 - x2) * (y3 - y4) == (y1 - y2) * (x3 - x4)