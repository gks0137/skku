word_list = input("문장 입력 : ").split()
word_set = set(word_list)

print("전체 단어: %d" % (len(word_list)))
print("유니크 단어: %d" % (len(word_set)))

for word in word_set:
    word_list.remove(word)
word_set = set(word_list)

print("중복 출현 단어:", end="")

comma = False
for word in word_set:
    print("%s %s %d" % (',' if comma else '', word, word_list.count(word) + 1), end='')
    comma = True