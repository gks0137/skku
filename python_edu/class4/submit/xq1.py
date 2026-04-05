import random

correct_numbers = [random.randint(0, 9) for _ in range(3)]

def check_number(numbers : list[str, str, str]) -> str:
    ball_count = 0
    strike_count = 0
    for correct, answer in zip(correct_numbers, numbers):
        if correct == int(answer):
            strike_count += 1
        elif int(answer) in correct_numbers:
            ball_count += 1
    
    def maessage(what, count):
        if count == 0:
            return ""
        else:
            return f"{count} {what}"
    
    result = maessage("BALL", ball_count) + " " + maessage("STRIKE", strike_count)

    if result == ' ':
        return " O U T"
    else:
        return result


play = input("Play game? (y, n) : ")
if play != 'y':
    print("EXIT GAME...")
    exit()

for rounds in range(1, 10):
    print(f"*** BASEBALL GAME .... ROUND : {rounds}")
    numbers = [input("1st number : "), input("2nd number : "), input("3rd number : ")]
    result = check_number(numbers)
    print("COMPUTER :" + result + " !!!!")

    if result == " 3 STRIKE":
        print("USER WINNER !!!!")
        exit()

print("USER LOST....\nthe answer was", *correct_numbers)