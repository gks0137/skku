N = int(input("밑변의 길이를 입력하시오: "))

for n_th_line, star_count in zip(range(N-1, -1, -1), range(1, N+1)):
    print(" " * n_th_line, end="")
    for star in range(star_count):
        print("*", end="")
        print(" ", end="")
    print()