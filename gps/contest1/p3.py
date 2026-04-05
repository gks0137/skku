abc = bytearray([101]*52)
abcd = input()
def abcde(c):
    return ord(c)-65 if ord(c)<91 else ord(c)-97+26
for c in abcd:
    abc[abcde(c)] += -100 if abc[abcde(c)]>100 else 1
k = min(abc)
for c in abcd:
    print(c if abc[abcde(c)]<2*k else '', end='')