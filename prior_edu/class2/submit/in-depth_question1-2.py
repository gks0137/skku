N = int(input("마름모의 길이를 입력하시오: "))

def print_line(star_count):
    for repeat in range(N):
        if repeat >= N-star_count:
            print("*", end="")
        print(" ", end="")
    print()

stars_in_line = list(range(1, N+1)) + list(range(N-1, 0, -1)) 
for star_count in stars_in_line:
    print_line(star_count)