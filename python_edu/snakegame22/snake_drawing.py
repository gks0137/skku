"""
drawing functions used by Snake_class and Snake game.
"""
from __future__ import annotations

import pygame
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from snake_class import Snake
    from pygame import Surface

black = pygame.Color(0, 0, 0)
white = pygame.Color(255, 255, 255)
red = pygame.Color(255, 0, 0)
green = pygame.Color(0, 255, 0)
blue = pygame.Color(0, 0, 255)
purple = pygame.Color(128, 0, 128)
dark_green = pygame.Color(0, 128, 0)

SNAKE_size: int = 20

def SNAKE_size_move_skdr(d: int):
    global SNAKE_size
    SNAKE_size += d


_player_snake_name = 'player_snake'
_enemy_snake_name = 'enemy_snake'


def snake_draw_head(snake: type[Snake], main_window: Surface) -> None:
    '''draw the head of the snake'''
    x, y = snake.x_drawing, snake.y_drawing
    dead = snake.is_dead
    dx, dy = snake.direction_current.to_vector()
    if _player_snake_name in type(snake).__name__:
        pygame.draw.rect(main_window, red if dead else green, pygame.Rect(x, y, SNAKE_size, SNAKE_size))
        pygame.draw.circle(main_window, red if dead else dark_green, (dx/4+x+SNAKE_size/2, dy/4+y+SNAKE_size/2), SNAKE_size/3, 0, True, True, True, True)
    elif _enemy_snake_name in type(snake).__name__:
        pygame.draw.rect(main_window, red if dead else blue, pygame.Rect(x, y, SNAKE_size, SNAKE_size))
        pygame.draw.circle(main_window, red if dead else purple, (dx/4+x+SNAKE_size/2, dy/4+y+SNAKE_size/2), SNAKE_size/3, 0, True, True, True, True)


def snake_draw_body(snake: type[Snake], main_window: Surface) -> None:
    '''draw the head of the snake'''
    x, y = snake.x_drawing, snake.y_drawing
    dead = snake.is_dead
    dark = snake.is_dark_or_bright()
    what = _player_snake_name in type(snake).__name__
    if dead:
        col = red
    elif dark:
        col = dark_green if what else purple
    else:
        col = green if what else blue
    pygame.draw.rect(main_window, col, pygame.Rect(x, y, SNAKE_size, SNAKE_size))
    
    '''if snake.after.direc is snake.direc:
        return
    square = [(x, y), (x+SNAKE_SIZE, y), 
             (x+SNAKE_SIZE, y+SNAKE_SIZE), (x, y+SNAKE_SIZE)]'''
    '''
    if snake.direc.turn_right() is snake.after.direc:
        sqare.pop(snake.direc.value)
    else:
        sqare.pop(snake.direc.turn_right().value)
    pygame.draw.polygon(main_window, col, square)'''
    '''
    arc = [False, False, False, False]
    if snake.direc.turn_right() is snake.after.direc:
        arc[(5-snake.direc.value)%4] = True
        pygame.draw.circle(main_window, col, square[snake.direc.opposite().value], SNAKE_SIZE, 0, *arc)
    else:
        arc[(4-snake.direc.value)%4] = True
        pygame.draw.circle(main_window, col, square[snake.direc.turn_left().value], SNAKE_SIZE, 0, *arc)
    '''


    

def snake_draw_tail(snake: type[Snake], main_window: Surface) -> None:
    '''draw the head of the snake'''
    x, y = snake.x_drawing, snake.y_drawing
    dead = snake.is_dead
    dark = snake.is_dark_or_bright()
    
    what = _player_snake_name in type(snake).__name__
    if dead:
        col = red
    elif dark:
        col = dark_green if what else purple
    else:
        col = green if what else blue
    pygame.draw.rect(main_window, col, pygame.Rect(x, y, SNAKE_size, SNAKE_size))
        



def draw_background(main_window: Surface, size: tuple[int, int], snake_frame: tuple[int, int], offset: tuple[int, int] = (0, 0), ) -> None:
    '''draw background'''
    
    main_window.fill(white)
    pygame.draw.rect(main_window, black, pygame.Rect(offset[0], offset[1], snake_frame[0], snake_frame[1]))




#test
if __name__ == '__main__':
    from snake_class import *

    frame = (720, 480)
    food_pos = [SNAKE_size*3, SNAKE_size*3]

    pygame.init()
    main_window = pygame.display.set_mode(frame)

    Snake.initialize_snake(main_window, frame, (0, 0), (SNAKE_size*5, SNAKE_size*5, Direction(1)))
    Snake.add(Direction(1))
    Snake.add(Direction(2))
    Snake.add(Direction(1))



    ###############################################################################################################
    #test functions

    draw_background(main_window, frame, frame)
    #draw_score(main_window, frame, 1, 15)

    #draw_gameover(main_window, frame)
    #draw_score(main_window, frame, 0, 15)
    
    Snake.draw()

    #draw_food(main_window, food_pos)

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
    
        


