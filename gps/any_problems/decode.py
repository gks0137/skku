for _ in range(int(input())):
    s = input()
    alphabets = [0] * 26
    for i in s:
        if i.isalpha():
            alphabets[ord(i) - ord('a')] += 1
    
    max = 0
    idx = -1
    for i in range(26):
        if alphabets[i] > max:
            max = alphabets[i]
            idx = i
        elif alphabets[i] == max and max != 0:
            idx = -1
    
    if idx == -1:
        print("?")
    else:
        print(chr(idx + ord('a')))