import random

def Check_Num(n) -> str:
    if n < N:
        return "UP"
    elif n > N:
        return "DOWN"
    else:
        return "SUCCESS"

N = random.randrange(1, 100)

print("Game Start!")
while True:
    n = int(input("n: "))
    print(Check_Num(n))
    if Check_Num(n) == "SUCCESS":
        break