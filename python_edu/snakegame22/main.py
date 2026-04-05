# ### Pygame Example

# %% [markdown]
# #### 0. 예제 설명(Introduction)
# Pygame은 쉽게 Game을 제작할 수 있도록 만들어진 module의 집합입니다.
# Python과 제공되는 간단한 몇가지의 함수만을 사용하여 실제로 구동할 수 있는 수준으로 만들 수 있습니다.
# 자세한 사항은 [Pygame Homepage](https://www.pygame.org/)를 참조해주세요.
#
# Pygame is a set of python module for writing game easliy.
# This allows you to create fully featured games and multimedia programs in the python language.
# You can see more details in [Pygame Homepage](https://www.pygame.org/).

# %% [markdown]
# ##### 0-1. 사전 준비(prerequirements)
# Pygame을 사용하기 위해 `pip`를 통한 pygame library를 설치합니다.
# 이 코드는 시작 후 한번만 실행해도 됩니다.
#
# You should install Pygame library with `pip` module
# This code only needs to be run once after startup.

# %%
# Jupyter 내부에서 shell command 실행을 위해 '%'를 사용하여 'pip'를 실행합니다.
# Insert `%` before running 'pip' command for running shell commands on Jupyter
# %pip install pygame

# %%
# Python으로 실행하고 싶으시다면 위 코드를 삭제하시고 아래의 코드를 실행해주세요.
# Delete the '%pip' code and run this code if you want to run on python
import sys
'''
import subprocess

subprocess.check_call([sys.executable, '-m', 'pip', 'install', 'pygame'])
'''
# %% [markdown]
# #### 1. 모듈 임포트(Module import)
# 설치한 pygame library 및 기타 필요한 모듈을 사용하기 위해 import합니다.
#
# Import `pygame library` and other modules to use in this code

# %%
# Pygame module import
import pygame
# 시간 확인, random 부여 등을 위한 module import
# Modules for time checking and randomization
import random
import time

from snake_drawing import *
from direction_class import *
from snake_class import *
from enemy_snake_class import *
from food_class import *
from gameover_drawing import *


# %% [markdown]
# ##### 1-1. 게임 사전 설정(Settings on the game)
# 게임에 대한 기본적인 설정에 대한 변수 들을 미리 정의합니다.
#
# Define variables that initializes the game

# %%
# Frame 수 조절(초당 그려지는 수)
# Framerate per seconds
fps = 60

# 창의 크기
# Window size
frame = (1080, 720)

# 시간을 흐르게 하기 위한 FPS counter
# FPS (frames per second) controller
fps_controller = pygame.time.Clock()

#%%
# Game 관련 변수들
# Game variables



score: int = 0

# %% [markdown]
# ##### 1-2. Pygame 초기화(Initialize Pygame)
# Pygame을 사용하기 위해 창 크기, 제목 등을 주어 초기화를 해줍니다.
# 만약 초기화를 실패하였다면 오류를 알려주고 종료하도록 합니다.
# 함수로 만들어서 게임이 동작하기 전에 부를 수 있도록 합니다.
#
# Initialize Pygame with window size, and title.
# When initializing Pygame failed, prints error and exit program.
# Run before executing main logic of the game.


# %%
def Init(size):
    # 초기화 후 error가 일어났는지 알아봅니다.
    # Checks for errors encountered
    check_errors = pygame.init()

    # pygame.init() example output -> (6, 0)
    # 두번째 항목이 error의 수를 알려줍니다.
    # second number in tuple gives number of errors
    if check_errors[1] > 0:
        print(
            f'[!] Had {check_errors[1]} errors when initialising game, exiting...')
        sys.exit(-1)
    else:
        print('[+] Game successfully initialised')

    # pygame.display를 통해 제목, window size를 설정하고 초기화합니다.
    # Initialise game window using pygame.display
    pygame.display.set_caption('Snake Example with PyGame')
    game_window = pygame.display.set_mode(size)
    return game_window

# %% [markdown]
# ##### 1-3. 기본 logic 함수 모음(basic logics of the game)
# 게임을 플레이하기 위해 필요한 함수들의 모음입니다.
# 자세한 부분은 각 주석을 확인해주세요.
#
# This is the set of functions that are required in the game.
# You can see more details in comments on each cell.

def frame_controller(snake_frame_dx: int = 0, snake_frame_dy: int = 0):
    global snake_frame_offset, snake_frame_size

    snake_frame_size = (snake_frame_size[0]+snake_frame_dx, snake_frame_size[1]+snake_frame_dy)

    
    Snake.move_frame(snake_frame_dx, snake_frame_dy)
    Food.move_frame(snake_frame_dx, snake_frame_dy)

def offset_controller(offset_dx: int = 0, offset_dy: int = 0, move_snakes: bool = True):
    global snake_frame_offset, snake_frame_size

    snake_frame_offset = (snake_frame_offset[0]+offset_dx, snake_frame_offset[1]+offset_dy)

    Snake.move_offset(offset_dx, offset_dy, move_snakes)
    Food.move_offset(offset_dx, offset_dy, move_snakes)
# %%
# Score


# %%
# Game Over
def game_over(window, size):
    # 'Game Over'문구를 띄우기 위한 설정입니다.
    # Settings of the 'Game Over' string to show on the screen
    
    player_snake_1.game_over()
    time.sleep(1)
    draw_gameover(window, size)

    # 'draw_score' 함수를 부릅니다.
    # Call 'draw_score' function.
    #draw_score(window, size, 0, score)
    scoreboard = [('player1', score), *[('enemy', enemy_score) for enemy_score in get_enemy_score()]]
    draw_scoreboard(main_window, frame, 0, scoreboard)

    # 그려진 화면을 실제로 띄워줍니다.
    # Show drawn windows to screen
    pygame.display.flip()

    # 3초 기다린 후 게임을 종료합니다.
    # exit program after 3 seconds.
    time.sleep(3)
    pygame.quit()
    sys.exit()


# %%
# Keyboard input
# this was replaced by Snake class method function

# %% [markdown]
# #### 2. 메인 프로그램
# Game이 동작하기 위한 메인 코드 입니다.
#
# This is main code of the game.
class player_snake_1(Snake):
    key_map = None
'''
class player_snake_2(Snake):
    key_map = 'asdf'

'''

HOWMANY_ENEMIES = 5
for i in range(HOWMANY_ENEMIES):
    type(f'enemy_snake_{i}', (enemy_snake,), {})


# %%
# 초기화합니다.
# Initialize
main_window = Init(frame)

snake_frame_size = (900, 700)
snake_frame_offset = (90, 10)
offset_dy = -2
offset_dx = -3
frame_motion = 0

move_snake = Snake.snake_animation_delay()

Food.initialize_Food(main_window, snake_frame_size, snake_frame_offset)
Snake.initialize_snake(main_window, snake_frame_size, snake_frame_offset)

player_snake_1.add_first_snake(SNAKE_size*5, SNAKE_size*10, Direction.RIGHT)
for _ in range(5):
    player_snake_1.add(Direction.RIGHT)

for enemy_snake_one in enemy_snake_dict.values():
    enemy_snake_one.add_first_snake(SNAKE_size*(random.randrange(0, 45)), SNAKE_size*(random.randrange(0, 10)), Direction.DOWN)
    for _ in range(5):
        enemy_snake_one.add(Direction.DOWN)

Food.spawn_food_random(random.randint(15, 25))

while True:
    # 게임에서 event를 받아옵니다.
    # Get event from user
    for event in pygame.event.get():
        # 종료시 실제로 프로그램을 종료합니다.
        # Close program if QUIT event occured
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            # esc 키를 눌렀을떄 종료 신호를 보냅니다.
            # Create quit event when 'esc' key pressed
            if event.key == pygame.K_ESCAPE:
                pygame.event.post(pygame.event.Event(pygame.QUIT))
            else:
                # 입력 키로 방향을 얻어냅니다.
                # Get direction with key
                #player_direction = get_keyboard(event.key, player_direction)
                player_snake_1.get_keyboard(event.key)
                #player_snake_2.get_keyboard(event.key)
    
    
    # if offset_dy < 0:
    #     if snake_frame_offset[1] <= 0:
    #         offset_dy *= -1
    # else:
    #     if snake_frame_offset[1] + snake_frame_size[1] >= frame[1]:
    #         offset_dy *= -1
    # if offset_dx < 0:
    #     if snake_frame_offset[0] <= 0:
    #         offset_dx *= -1
    # else:
    #     if snake_frame_offset[0] + snake_frame_size[0] >= frame[0]:
    #         offset_dx *= -1
    # offset_controller(offset_dx, offset_dy)

    # if frame_motion != 0:
    #     frame_motion = 0
    # else:
    #     if random.randint(1, 60) == 1:
    #         frame_motion = -SNAKE_SIZE
    #         if random.randint(0, 1) == 0:
    #             offset_controller(SNAKE_SIZE, SNAKE_SIZE, False)

    # frame_controller(frame_motion, frame_motion)


    if next(move_snake):
        
        # 실제로 뱀의 위치를 옮깁니다.
        # Move the actual snake position
        player_snake_1.add()

        #player_snake.print_snakes()
        snake_pos = player_snake_1.head_pos()
        # 우선 증가시키고 음식의 위치가 아니라면 마지막을 뺍니다.
        # Grow snake first, check if food is on sanke head(if not, delete last)
        food_ate = Food.eat_food(snake_pos)
        if food_ate:
            score += 1
        else:
            player_snake_1.pop()

        # 음식이 없다면 음식을 랜덤한 위치에 생성합니다.
        # Spawning food on the screen with random position
        if not Food.is_food_spawned():
            Food.spawn_food_random(random.randint(20, 40))
        
        #player_snake_2.add()
        #player_snake_2.pop()

        #enemy snake 이동
        move_enemy_snakes()
            

    # 우선 게임을 검은 색으로 채우고 뱀의 각 위치마다 그림을 그립니다.
    # Fill the screen black and draw each position of snake
    draw_background(main_window, frame, snake_frame_size, snake_frame_offset)

    # 점수를 띄워줍니다.
    # Show score with defined function
    scoreboard = [('player1', score), *[('enemy', enemy_score) for enemy_score in get_enemy_score()]]
    draw_scoreboard(main_window, frame, 1, scoreboard)

    # 음식을 그립니다.
    # Draw snake food
    Food.draw()

    player_snake_1.draw()
    #player_snake_2.draw()
    draw_enemy_snakes()


    # Game Over 상태를 확인합니다.
    # Check Game Over conditions

    #enemy snake check
    check_enemy_snakes()

    # 바깥 벽 처리를 합니다.
    # Check if the snake hit the wall
    if player_snake_1.is_hit_wall():
        game_over(main_window, frame)

    # 뱀의 몸에 닿았는지 확인합니다.
    # Check if the snake is hit itself
    if player_snake_1.is_hit_itself():
        game_over(main_window, frame)

    

    # 실제 화면에 보이도록 업데이트 해줍니다.
    # Refresh game screen
    pygame.display.update()

    # 해당 FPS만큼 대기합니다.
    # Refresh rate
    fps_controller.tick(fps)

