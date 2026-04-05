"""
drawing functions used by Snake game.
"""
import pygame
from pygame import Surface

black = pygame.Color(0, 0, 0)
red = pygame.Color(255, 0, 0)
green = pygame.Color(0, 255, 0)


def draw_gameover(main_window: Surface, size: tuple[int, int]) -> None:
    '''
    draw game over screen
    '''
    my_font = pygame.font.SysFont('times new roman', 90)
    game_over_surface = my_font.render('Game Over', True, red)
    game_over_rect = game_over_surface.get_rect()
    game_over_rect.midtop = (size[0]/2, size[1]/4)

    # window를 검은색으로 칠하고 설정했던 글자를 window에 복사합니다.
    # Fill window as black and copy 'Game Over' strings to main window.
    main_window.fill(black)
    main_window.blit(game_over_surface, game_over_rect)




def draw_score(window: Surface, size: tuple[int, int], choice: int, score: int) -> None:
    '''draw score\n
    choice = 0  |  show at center\n
    choice = 1  |  show at top left
    '''
    # Score를 띄우기 위한 설정입니다.
    # Settings for showing score on screen
    color = green
    score_font = pygame.font.SysFont('consolas' if choice else 'times', 20)
    score_surface = score_font.render('Score : ' + str(score), True, color)
    score_rect = score_surface.get_rect()

    # Game over 상황인지 게임중 상황인지에 따라 다른 위치를 선정합니다.
    # Select different location depending on the situation.
    if choice == 1:
        score_rect.midtop = (size[0]/10, 15)
    else:
        score_rect.midtop = (size[0]/2, size[1]/1.25)

    # 설정한 글자를 window에 복사합니다.
    # Copy the string to windows
    window.blit(score_surface, score_rect)

def draw_scoreboard(window: Surface, size: tuple[int, int], choice: int, scores: list[tuple[str, int]]) -> None:
    '''draw score\n
    choice = 0  |  show at center\n
    choice = 1  |  show at top left
    '''
    # Score를 띄우기 위한 설정입니다.
    # Settings for showing score on screen
    color = green
    score_font = pygame.font.SysFont('consolas' if choice else 'times', 20)

    scores.sort(reverse=True, key=lambda x: x[1])
    scoreboard = ["<Scoreboard>"]
    for namescore in scores:
        scoreboard.append(f'{namescore[0]} : {namescore[1]}')

    lines: list[tuple[Surface, pygame.Rect]] = []

    for line in scoreboard:
        score_surface = score_font.render(line, True, color)
        score_rect = score_surface.get_rect()
        lines.append((score_surface, score_rect))

    # Game over 상황인지 게임중 상황인지에 따라 다른 위치를 선정합니다.
    # Select different location depending on the situation.
    for i in range(len(lines)):
        if choice == 1:
            lines[i][1].midtop = (size[0]/10, 15 + 20*i)
        else:
            lines[i][1].midtop = (size[0]/2, size[1]/1.25 + 20*i)

    # 설정한 글자를 window에 복사합니다.
    # Copy the string to windows
    for score_surface, score_rect in lines:
        window.blit(score_surface, score_rect)


#test
if __name__ == '__main__':
    from snake_class import *
    import time
    frame = (720, 480)
    '''food_pos = [SNAKE_SIZE*3, SNAKE_SIZE*3]'''

    pygame.init()
    main_window = pygame.display.set_mode(frame)

    '''Snake.initialize_snake(main_window, frame, (SNAKE_SIZE*5, SNAKE_SIZE*5, Direction(1)))
    Snake.add(Direction(1))
    Snake.add(Direction(2))
    Snake.add(Direction(1))
    '''


    ###############################################################################################################
    #test functions


    draw_gameover(main_window, frame)
    draw_score(main_window, frame, 0, 15)
    draw_score(main_window, frame, 1, 15)


    #################################################################################################################



    pygame.display.update()

    while True:
        # 게임에서 event를 받아옵니다.
        # Get event from user
        for event in pygame.event.get():
            # 종료시 실제로 프로그램을 종료합니다.
            # Close program if QUIT event occured
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
    
        
