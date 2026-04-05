"""enemy snake class"""
from __future__ import annotations
from typing import ClassVar, Generator
import pygame
from pygame import Surface
import random

from snake_class import Snake
from snake_drawing import SNAKE_size
from food_class import Food
from direction_class import Direction

enemy_snake_dict: dict[str, type[enemy_snake]] = dict()

def howmany_enemy_survived():
    return len((enemy_snake_dict.keys()))

def move_enemy_snakes():
    for snake in enemy_snake_dict.values():
        snake.move()
    
def draw_enemy_snakes():
    for snake in enemy_snake_dict.values():
        snake.draw()

def check_enemy_snakes():
    for snake in enemy_snake_dict.copy().values():
        snake.check()

def get_enemy_score() -> list[int]:
    return [snake.score for snake in enemy_snake_dict.values()]
    

def turn_delay_gen() -> Generator[int]:
    while True:
        for _ in range(random.randint(4, 10)):
            yield False
        yield True

class enemy_snake(Snake):
    _turn_delay = turn_delay_gen()
    score: ClassVar[int] = 0

    def __init_subclass__(cls):
        super().__init_subclass__()
        global enemy_snake_dict
        enemy_snake_dict[cls.__name__] = cls
        cls._turn_delay = turn_delay_gen()

    @classmethod
    def move(cls) -> None:
        '''enemy snake 움직이기'''
        cls.update_enemy_direction()

        cls.add()
        if Food.eat_food(cls.head_pos()):
            cls.score += 1
        else:
            cls.pop()

    @classmethod
    def update_enemy_direction(cls):
        safe_candidates = []
        random_food = Food.get_nearest_pos(cls.head_pos())

        #근처에 음식이 없는 경우
        if random_food == None:
            for i in [0, 1, 2, 3]:
                d = Direction(i)
                if cls.is_direction_safe(d):
                    safe_candidates.append(d)
            
            if not safe_candidates:
                return

            if cls.direction_current in safe_candidates:
                rand_val = random.random()
                if rand_val < 0.6:
                    return
            
            cls.direction_queue.append(random.choice(safe_candidates))
            return
        
        # 근처에 음식이 있는 경우
        # 1. 일단 살 수 있는(안전한) 모든 방향을 찾습니다.
        for i in [0, 1, 2, 3]:
            d = Direction(i)
            if cls.is_direction_safe(d):
                vec = d.to_vector()
                next_pos = [cls.head_pos()[0] + vec[0], cls.head_pos()[1] + vec[1]]
                distance = abs(next_pos[0] - random_food[0]) + abs(next_pos[1] - random_food[1])
                safe_candidates.append({'direction': d, 'dist': distance})

        if not safe_candidates:
            return # 더 이상 갈 곳이 없음

        # 2. 안전한 방향들을 '먹이와의 거리' 순으로 정렬합니다.
        safe_candidates.sort(key=lambda x: x['dist'])

        # 3. 확률적 선택 (가장 중요한 부분!)
        # 80% 확률로 가장 최선의 방향을 선택하고, 
        # 20% 확률로 두 번째나 세 번째로 좋은(하지만 여전히 안전한) 방향을 선택합니다.
        
        rand_val = random.random()
        
        if len(safe_candidates) > 1 and rand_val < 0.0: 
            # 10% 확률로 '차선책' 선택 (뱀들이 갈라지는 효과)
            chosen_move = random.choice(safe_candidates[1:]) 
        else:
            # 80% 확률 또는 선택지가 하나뿐일 때 '최선책' 선택
            chosen_move = safe_candidates[0]

        cls.direction_queue.append(chosen_move['direction'])
    
    @classmethod
    def is_direction_safe(cls, direc: Direction) -> None:
        snake_pos = cls.head_pos()
        dx, dy = direc.to_vector()
        snake_pos = [snake_pos[0] + dx, snake_pos[1] + dy]
        
        for block in cls.snake_list:
            if snake_pos[0] == block.pos[0] and snake_pos[1] == block.pos[1]:
                return False
        if snake_pos[0] < cls.offset_x or snake_pos[0] > cls.offset_x + cls._frame[0] - SNAKE_size:
            return False
        if snake_pos[1] < cls.offset_y or snake_pos[1] > cls.offset_y + cls._frame[1] - SNAKE_size:
            return False
        return True


    @classmethod
    def check(cls) -> None:
        '''판정'''
        if cls.is_hit_itself() or cls.is_hit_wall():
            del enemy_snake_dict[cls.__name__]
            cls.game_over()
    
    @classmethod
    def move_snake_by_offset(cls, dx, dy) -> None:
        '''function overwirte : subsubclass 재설정 시키기'''
        for snake in enemy_snake_dict.values():
            snake.move_enemy_snake_by_offset(dx, dy)
    
    @classmethod
    def move_enemy_snake_by_offset(cls, dx, dy) -> None:
        '''subsubclass 재설정'''
        for snake in cls.snake_list:
            snake.x += dx
            snake.y += dy
    
    







