A, B = map(int, input("두 정수를 입력하세요: ").split())

quotient = (abs(A) // abs(B)) * (1 if (A * B) >= 0 else -1)
remainder = A - (quotient * B)


print(f"{A} / {B} 의 몫은 {quotient}입니다.")
print(f"{A} / {B} 의 나머지는 {remainder}입니다.")