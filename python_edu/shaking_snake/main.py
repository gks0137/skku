import sys

import pygame

import random
import time

from snake_drawing import *
from direction_class import *
from snake_class import *
from enemy_snake_class import *
from food_class import *
from gameover_drawing import *


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

normal_fps = 60
boost_fps = 120

max_energy = 400
energy = max_energy
energy_depletion = 2    # 스페이스 누를 때 매 프레임 감소량
energy_recovery = 0.5  

is_snake_boosting: bool = False

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

def SNAKE_size_move(d: int):
    global SNAKE_size
    SNAKE_size += d

    SNAKE_size_move_fdcl(d)
    SNAKE_size_move_skcl(d)
    SNAKE_size_move_skdr(d)

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


def screen_resize_anim(*delta: int):
    delta = list(delta)
    delta[2] += delta[0]
    delta[3] += delta[1]
    resize_queue = []
    is_needed_to_draw_warning = snake_frame_size == (800, 600)
    offset_destination = (snake_frame_offset[0]+delta[0], snake_frame_offset[1]+delta[1])

    for idx, motion in enumerate(delta):
        resize_queue.extend([(idx, SNAKE_size if motion>0 else -SNAKE_size)]*(abs(motion) // SNAKE_size))
    resize_queue.sort(key=lambda _: random.random())

    def move(i, movement):
        if i==0:
            frame_controller(-movement, 0)
            offset_controller(movement, 0, False)
        elif i==1:
            frame_controller(0, -movement)
            offset_controller(0, movement, False)
        elif i==2:
            frame_controller(movement, 0)
        elif i==3:
            frame_controller(0, movement)
    #print(delta, screen_resize_preview, len(resize_queue))
    for idx, motion in resize_queue:
        
        draw_background(main_window, frame, snake_frame_size, snake_frame_offset)
        if is_needed_to_draw_warning:
            pygame.draw.rect(main_window, pygame.Color(128, 0, 0), pygame.Rect(*snake_frame_offset, *snake_frame_size))
            pygame.draw.rect(main_window, pygame.Color(0, 0, 0), pygame.Rect(*offset_destination, *screen_resize_preview))
        
        
        
        Food.draw()
        player_snake_1.draw(moving=False)

        pygame.display.update()
        
        snake_frame_offset_old = (snake_frame_offset[0], snake_frame_offset[1])
        snake_frame_size_old = (snake_frame_size[0], snake_frame_size[1])


        move(idx, motion)

        if not is_needed_to_draw_warning:
            Food.spawn_food_exclusive(lambda pos:
            snake_frame_offset_old[0] <= pos[0] and snake_frame_offset_old[1] <= pos[1] and
            pos[0] < snake_frame_offset_old[0] + snake_frame_size_old[0] and
            pos[1] < snake_frame_offset_old[1] + snake_frame_size_old[1]
            , random.randint(20, 40) - Food.howmany_food)

        fps_controller.tick(fps)


def snake_resize_anim(d: int):
    global SNAKE_size
    
    delta_frame = snake_frame_size[0]//10 if d==1 else -snake_frame_size[0]//20
    if d==1:
        offset_preview = (random.randint(0, 280)*2, random.randint(0, 120)*2)
    else:
        offset_preview = snake_frame_offset
    delta_offset = [(offset_preview[0]-snake_frame_offset[0]) / 10, 
                    (offset_preview[1]-snake_frame_offset[1]) / 10]

    for _ in range(10):
        
        frame_controller(delta_frame, delta_frame)
        offset_controller(*delta_offset, move_snakes=False)
        SNAKE_size_move(d)

        draw_background(main_window, frame, snake_frame_size, snake_frame_offset)
        Food.draw()
        player_snake_1.draw(moving=False)
        pygame.display.update()

        fps_controller.tick(10)
    
    Snake.set_offset(*offset_preview)
    Food.set_offset(*offset_preview)

    print(SNAKE_size)
    





# %%
# Game Over
def game_over(window, size):
    # 'Game Over'문구를 띄우기 위한 설정입니다.
    # Settings of the 'Game Over' string to show on the screen
    
    player_snake_1.game_over()

    ##
    pygame.quit()
    sys.exit()
    ##

    time.sleep(1)
    draw_gameover(window, size)

    # 'draw_score' 함수를 부릅니다.
    # Call 'draw_score' function.
    draw_score(window, size, 0, score)

    # 그려진 화면을 실제로 띄워줍니다.
    # Show drawn windows to screen
    pygame.display.flip()

    # 3초 기다린 후 게임을 종료합니다.
    # exit program after 3 seconds.
    time.sleep(3)
    pygame.quit()
    sys.exit()


def frame_delay_generator(n) -> Generator[bool]:
    for _ in range(n):
        yield False
    yield True




# #### 2. 메인 프로그램
# Game이 동작하기 위한 메인 코드 입니다.
#
# This is main code of the game.
class player_snake_1(Snake):
    key_map = None

# class player_snake_2(Snake):
#     key_map = 'asdf'



# %%
# 초기화합니다.
# Initialize
main_window = Init(frame)

snake_frame_size = (800, 600)
snake_frame_offset = (90, 10)
offset_dy = 0
offset_dx = -3
frame_motion = 0

screen_move: bool = True
snake_size_moving: bool = False

screen_resize_delay = frame_delay_generator(random.randint(20, 40))

move_snake = Snake.snake_animation_delay()

Food.initialize_Food(main_window, snake_frame_size, snake_frame_offset)
Snake.initialize_snake(main_window, snake_frame_size, snake_frame_offset)

player_snake_1.add_first_snake(SNAKE_size*5, SNAKE_size*5, Direction.RIGHT)
for _ in range(5):
    player_snake_1.add(Direction.RIGHT)

# player_snake_2.add_first_snake(800-SNAKE_SIZE*5, 600-SNAKE_SIZE*10, Direction.LEFT)
# for _ in range(5):
#     player_snake_2.add(Direction.LEFT)

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
    
    keys = pygame.key.get_pressed()

    if keys[pygame.K_SPACE] and energy > 0:
        fps = boost_fps
        energy -= energy_depletion
        is_snake_boosting = True
    else:
        fps = normal_fps
        energy += energy_recovery
        is_snake_boosting = False

    energy = min(max_energy, energy)
    
    if screen_move:
        if offset_dy < 0:
            if snake_frame_offset[1] <= 0:
                offset_controller(0, -offset_dy)
                offset_dy = 0 if random.random()<0.5 else random.choice([2, 3, 4])
                offset_dx = random.choice([-4, -3, -2, 2, 3, 4])
        elif offset_dy > 0:
            if snake_frame_offset[1] + snake_frame_size[1] >= frame[1]:
                offset_controller(0, -offset_dy)
                offset_dy  = 0 if random.random()<0.5 else random.choice([-4, -3, -2])
                offset_dx = random.choice([-4, -3, -2, 2, 3, 4])

        if offset_dx < 0:
            if snake_frame_offset[0] <= 0:
                offset_controller(-offset_dx, 0)
                offset_dx = 0 if random.random()<0.5 else random.choice([2, 3, 4])
                offset_dy = random.choice([-4, -3, -2, 2, 3, 4])
        elif offset_dx > 0:
            if snake_frame_offset[0] + snake_frame_size[0] >= frame[0]:
                offset_controller(-offset_dx, -offset_dy)
                offset_dx = 0 if random.random()<0.5 else random.choice([-4, -3, -2])
                offset_dy = random.choice([-4, -3, -2, 2, 3, 4])
        offset_controller(offset_dx, offset_dy)




    if next(move_snake):
        
        # 실제로 뱀의 위치를 옮깁니다.
        # Move the actual snake position
        player_snake_1.add()

        #player_snake.print_snakes()
        snake_pos = player_snake_1.head_pos()
        # 우선 증가시키고 음식의 위치가 아니라면 마지막을 뺍니다.
        # Grow snake first, check if food is on sanke head(if not, delete last)
        if Food.eat_food(snake_pos):
            score += 1
        else:
            player_snake_1.pop()

        # 음식이 없다면 음식을 랜덤한 위치에 생성합니다.
        # Spawning food on the screen with random position
        if not Food.is_food_spawned():
            Food.spawn_food_random(random.randint(20, 40))
        
        #player_snake_2.add()
        #player_snake_2.pop()

        if screen_move:
            if snake_frame_size == (800, 600):
                if next(screen_resize_delay):
                    screen_move = False
                    screen_resize_delay = frame_delay_generator(15)
                    temp = False

                    screen_resize_x = random.randint(400//SNAKE_size - 5, 400//SNAKE_size + 5) * SNAKE_size
                    screen_resize_y = random.randint(300//SNAKE_size, 300//SNAKE_size + 5) * SNAKE_size
                    if screen_resize_x<400 and screen_resize_y<400:
                        snake_size_moving = True
                    screen_resize_preview = (screen_resize_x, screen_resize_y)
                    screen_resize_offset_d = (random.randint(0, (800-screen_resize_x)//SNAKE_size) * SNAKE_size, 
                                            random.randint(0, (600-screen_resize_y)//SNAKE_size) * SNAKE_size)
            else:
                if next(screen_resize_delay):
                    screen_move = False
                    screen_resize_delay = frame_delay_generator(0)
        else:
            if not is_snake_boosting:
                temp = next(screen_resize_delay)
            else:
                pass
            if temp:
                
                screen_move = True
                if snake_frame_size == (800, 600):
                    screen_resize_delay = frame_delay_generator(random.randint(45, 120))
                    # 줄어들기
                    screen_resize_anim(*screen_resize_offset_d, screen_resize_x-800, screen_resize_y-600)
                elif True or not snake_size_moving:
                    screen_resize_delay = frame_delay_generator(random.randint(45, 120))
                    # 늘어나기
                    screen_resize_offset_preview = [
                        snake_frame_offset[0]%SNAKE_size + 
                        random.randrange(max(0, snake_frame_offset[0]+snake_frame_size[0]-800-snake_frame_offset[0]%SNAKE_size), 
                                        min(snake_frame_offset[0]-snake_frame_offset[0]%SNAKE_size + 1, 280), SNAKE_size), 
                        snake_frame_offset[1]%SNAKE_size + 
                        random.randrange(max(0, snake_frame_offset[1]+snake_frame_size[1]-600-snake_frame_offset[1]%SNAKE_size), 
                                        min(snake_frame_offset[1]-snake_frame_offset[1]%SNAKE_size + 1, 120), SNAKE_size)
                        ]

                    screen_resize_anim(screen_resize_offset_preview[0] - snake_frame_offset[0], 
                                    screen_resize_offset_preview[1] - snake_frame_offset[1], 
                                    800 - screen_resize_x, 600 - screen_resize_y)
                    #Food.spawn_food_random(random.randint(20, 40) - Food.howmany_food)
                else:
                    screen_resize_delay = frame_delay_generator(random.randint(45, 75))
                    if snake_frame_size == screen_resize_preview:
                        snake_resize_anim(1)
                    else:
                        snake_resize_anim(-1)
                        snake_size_moving = False
                    




    # 우선 게임을 검은 색으로 채우고 뱀의 각 위치마다 그림을 그립니다.
    # Fill the screen black and draw each position of snake
    draw_background(main_window, frame, snake_frame_size, snake_frame_offset)

    # screen이 resize 예정인 경우 붉은색 영역을 표시
    if not screen_move:
        if snake_frame_size == (800, 600):
            pygame.draw.rect(main_window, pygame.Color(128, 0, 0), pygame.Rect(*snake_frame_offset, *snake_frame_size))
            pygame.draw.rect(main_window, pygame.Color(0, 0, 0), pygame.Rect(
                snake_frame_offset[0]+screen_resize_offset_d[0], snake_frame_offset[1]+screen_resize_offset_d[1],
                *screen_resize_preview))
        else:
            pass
        


    # 점수를 띄워줍니다.
    # Show score with defined function
    draw_score(main_window, frame, 1, score)

    # 음식을 그립니다.
    # Draw snake food
    Food.draw()


    # 에너지 바
    bar_x = 950
    bar_y = 10
    bar_width = 100
    bar_height = 10
    energy_ratio = energy / max_energy
    current_width = int(bar_width * energy_ratio)

    pygame.draw.rect(main_window, black, (bar_x, bar_y, bar_width, bar_height))
    pygame.draw.rect(main_window, green, (bar_x, bar_y, current_width, bar_height))



    player_snake_1.draw()
    #player_snake_2.draw()


    # Game Over 상태를 확인합니다.
    # Check Game Over conditions


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

