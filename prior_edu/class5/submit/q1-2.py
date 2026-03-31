print("끝말잇기 게임을 시작합니다")
prev_word = input("첫 단어를 말해주세요: ")
expired_words = {prev_word}
print(prev_word)
print()


playing = True
while playing:
    next_word = input("다음 단어를 말해주세요: ")
    if next_word in expired_words:
        print("이미 사용한 단어입니다!")
        playing = False

    if prev_word[-1] != next_word[0]:
        print("끝말이 일치하지 않습니다!")
        playing = False
    
    if playing:
        print(prev_word + '->' + next_word)
        print()
