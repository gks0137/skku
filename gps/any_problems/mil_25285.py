for _ in range(int(input())):
    h, w = map(int, input().split())
    bmi  = w / (h/100)**2
    if h < 140.1:
        print("6")
    elif h < 146:
        print("5")
    elif h < 159:
        print("4")
    elif h < 161:
        if bmi < 16 or bmi >= 35:
            print("4")
        else:
            print("3")
    elif h < 204:
        if bmi < 16 or bmi >= 35:
            print("4")
        elif bmi < 18.5 or bmi >= 30:
            print("3")
        elif bmi < 20 or bmi >= 25:
            print("2")
        else:
            print("1")
    else:
        print("4")