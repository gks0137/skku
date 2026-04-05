import random

def generate_numbers() -> list:
    return [random.randint(1, 9) for _ in range(3)]

def check_numbers(three_numbers : list) -> int:
    score = 3-len(set(three_numbers))
    if score == 2 and 7 in three_numbers:
        score = 5   #jackpot
        jackpot_count += 1
    return score

def where_to_check() -> list:
    def my_zip(lst1, lst2) -> list:
        lst1 = [lst1] * 3 if type(lst1) == int else lst1
        lst2 = [lst2] * 3 if type(lst2) == int else lst2
        return list(zip(lst1, lst2))
    return [my_zip(indexes, indexes[i]) for i in indexes] + [my_zip(indexes[i] ,indexes) for i in indexes] + [my_zip(indexes, indexes[::i]) for i in [1, -1]]

total_score = 0
jackpot_count = 0
indexes = list(range(3))

while True:
    numbers = [generate_numbers() for _ in range(3)]
    print("뽑힌 숫자", *[' '.join(map(str, numbers[row])) for row in range(3)], sep="\n")

    score = 0
    for check in where_to_check():
        score += check_numbers([numbers[i][j] for i, j in check])

    total_score += score
    
    print("얻은 점수:  ", score)
    stop = input("그만하시겠습니까?: ")
    if stop == 'y':
        break

print(f"총 점수: {total_score} , 잭 팟 횟수: {jackpot_count}")