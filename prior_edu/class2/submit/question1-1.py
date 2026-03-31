dress_num = int(input("원피스의 개수를 입력하시오:\n"))
sweater_num = int(input("스웨터의 개수를 입력하시오:\n"))

price = (dress_num * 50000) + (sweater_num * 30000)

if price < 100000:
    total_price = price * 0.95
elif 100000 <= price < 200000:
    total_price = price * 0.9
else:
    total_price = price * 0.8

print(f"총액: {int(total_price)}")
