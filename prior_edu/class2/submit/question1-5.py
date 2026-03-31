M = int(input("가로 길이를 입력하시오: "))
N = int(input("세로 길이를 입력하시오: "))

for i in range(N):
    for j in range(M):
        print("*", end="")
    print()