n = input("n: ")
n_set = set(n)
N_set = set('12345')

if len(n) == 5 and n_set == N_set:
    print("n(%s)은 12345와 쌍둥이입니다." % (n))
else:
    print("n(%s)은 12345와 쌍둥이가 아니며, " \
    "포함되지 않는 숫자들은 {%s} 입니다." % (n, ', '.join(n_set.difference(N_set))))