import random

def generate_numbers() -> list:
    three_numbers = []
    for rand_num in range(3):
        three_numbers.append(random.randint(1, 9))

    return three_numbers


def check_numbers(three_numbers) -> int:

    different_numbers = set(three_numbers)

    score = 3-len(different_numbers)

    #jackpot
    if score == 2 and 7 in different_numbers:
        score = 5
        jackpot_count += 1
    
    return score

total_score = 0
jackpot_count = 0

while True:
    numbers = generate_numbers()
    print("뽑힌 숫자 ", *numbers)
    score = check_numbers(numbers)
    total_score += score
    print("얻은 점수: ", score)
    stop = input("그만하시겠습니까?: ")
    if stop == 'y':
        break

print(f"총 점수: {total_score} , 잭 팟 횟수: {jackpot_count}")