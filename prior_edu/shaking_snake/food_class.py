"""food class"""
from __future__ import annotations
from typing import ClassVar, Generator, Union
import pygame
from pygame import Surface

import random

from snake_drawing import SNAKE_size

def SNAKE_size_move_fdcl(d: int):
    global SNAKE_size
    SNAKE_size += d

EATING_ANIMATION_FRAME: int = 5
FOOD_SCEARCHING_LIMIT = 30

class Food:
    """Food class 설명"""
    offset_x: ClassVar[int] = 0
    offset_y: ClassVar[int] = 0
    _main_window: ClassVar[Surface] = None
    _frame: ClassVar[tuple[int, int]] = None
    food_list: ClassVar[list[Food]] = []
    food_pos_list: ClassVar[list[tuple[int, int]]] = []
    howmany_food: ClassVar[int] = 0

    def __init__(self, pos: tuple[int, int] = None, special: str = None) -> None:
        if not pos:
            self.x = random.randrange(0, (Food._frame[0]//SNAKE_size)) * SNAKE_size + Food.offset_x
            self.y = random.randrange(0, (Food._frame[1]//SNAKE_size)) * SNAKE_size + Food.offset_y
        else:
            self.x, self.y = pos
        self.special: str = special
        self.is_eaten: bool = False

        Food.food_list.append(self)
        Food.food_pos_list.append((self.x, self.y))
        Food.howmany_food += 1
        #print('food spawned')

    @property
    def pos(self) -> tuple[int, int]:
        '''Food의 위치 (x, y)'''
        return (self.x, self.y)
    
    @staticmethod
    def random_pos() -> tuple[int, int]:
        '''전체 food 중 랜덤 food의 위치 반환'''
        return random.choice(Food.food_pos_list)
    
    @staticmethod
    def get_nearest_pos(pos: tuple[int, int]) -> Union[tuple[int, int], None]:
        '''가장 가까운 위치의 food의 pos 반환, 거리 20 이내에 없으면 None 반환'''
        if not Food.food_list:
            raise IndexError("no food to get position of")
        candidates = []

        for food_pos in Food.food_pos_list:
            dist = abs(pos[0] - food_pos[0]) + abs(pos[1] - food_pos[1])
            candidates.append({'return':food_pos, 'dist':dist})
        
        candidates.sort(key=lambda x: x['dist'])
        
        if candidates[0]['dist'] < FOOD_SCEARCHING_LIMIT*SNAKE_size:
            return candidates[0]['return']
        else:
            return None

    @staticmethod
    def is_food_spawned() -> bool:
        '''Food가 생성되어 있는지 bool로 반환'''
        if Food.food_list:
            return True
        return False
    
    @staticmethod
    def initialize_Food(main_window: Surface, size:tuple[int, int], offset: tuple[int, int]) -> None:
        '''게임 시작 시의 Food 설정'''
        Food._main_window = main_window
        Food._frame = size
        Food.offset_x, Food.offset_y = offset

        
    @staticmethod
    def move_offset(dx: int = 0, dy: int = 0, move_foods: bool = True) -> None:
        '''offset 이동'''
        Food.offset_x += dx
        Food.offset_y += dy
        if move_foods:
            for food in Food.food_list:
                food.x += dx
                food.y += dy
            for i, food_pos in enumerate(Food.food_pos_list):
                Food.food_pos_list[i] = (food_pos[0] + dx, food_pos[1] + dy)
    
    @staticmethod
    def set_offset(x: int = 0, y: int = 0, move_foods: bool = True) -> None:
        '''offset 설정'''
        Food.move_offset(x-Food.offset_x, y-Food.offset_y, move_foods)

    @staticmethod
    def set_frame(x: int = 720, y: int = 480) -> None:
        '''frame 설정'''
        Food._frame = (x, y)
    
    @classmethod
    def move_frame(cls, dx: int = 720, dy: int = 480) -> None:
        '''frame 설정'''
        cls._frame = (dx + cls._frame[0], dy + cls._frame[1])

    def is_hit_wall(self) -> bool:
        food_pos = self.pos
        if food_pos[0] < Food.offset_x or food_pos[0] > Food.offset_x + Food._frame[0] - SNAKE_size:
            return True
        if food_pos[1] < Food.offset_y or food_pos[1] > Food.offset_y + Food._frame[1] - SNAKE_size:
            return True
        return False

    @staticmethod
    def spawn_food_random(n: int = 1, special: str = None) -> None:
        '''
        n번 반복 -> 랜덤 위치에 Food 생성 \n
        food의 위치가 겹치면 삭제
        '''
        for _ in range(n):
            Food(special=special)
            spawned_food = Food.food_list[-1]
            if spawned_food.pos in Food.food_pos_list[:-1]:
                spawned_food.delete()
    
    @staticmethod
    def spawn_food_xy(x: int, y: int, special: str = None) -> None:
        '''
        (x, y)에 Food 생성 \n
        food의 위치가 겹치면 삭제
        '''
        Food((x, y), special=special)
        spawned_food = Food.food_list[-1]
        if spawned_food.pos in Food.food_pos_list[:-1]:
            spawned_food.delete()

    @staticmethod
    def spawn_food_exclusive(key: function[bool], n: int = 1, special: str = None) -> None:
        '''
        랜덤 위치에 food n개 생성 \n
        food의 위치가 겹치면 삭제 \n
        key 함수에 food의 pos를 전달했을 때 True를 반환하면 삭제
        '''
        for _ in range(n):
            Food.spawn_food_random(special=special)
            spawned_food = Food.food_list[-1]
            if spawned_food.pos in Food.food_pos_list[:-1]:
                spawned_food.delete()
            elif key(spawned_food.pos):
                spawned_food.delete()



    @staticmethod
    def draw() -> None:
        '''Food 그리기'''
        for food in Food.food_list:
            food.draw_one_food()

    def draw_one_food(self) -> None:
        if not self.is_eaten:
            if self.is_hit_wall():
                self.delete()
            draw_food(Food._main_window, self.pos)
            return
        anim = next(self.eating_anim)
        if anim != EATING_ANIMATION_FRAME:
            draw_food(Food._main_window, self.pos, eaten_anim=anim)
            return
        self.delete()

    @staticmethod
    def eat_food(snake_pos: tuple[int, int]) -> Union[bool, str]:
        '''snake가 food를 먹었는지 반환'''
        for food in Food.food_list:
            if food.is_eaten:
                return False
            if snake_pos == food.pos:
                food.eaten()
                return food.special if food.special != None else True
        return False

    def eaten(self) -> None:
        self.is_eaten = True
        Food.howmany_food -= 1
        self.eating_anim = Food.eating_animation_generator()
    
    def delete(self)-> None:
        Food.howmany_food -= 1
        Food.food_list.remove(self)
        Food.food_pos_list.remove(self.pos)
        del self


    @staticmethod
    def eating_animation_generator() -> Generator[int]:
        for n in range(1, EATING_ANIMATION_FRAME+1):
            yield n


red = pygame.Color(255, 0, 0)
yellow = pygame.Color(255, 255, 0)
white = pygame.Color(255, 255, 255)


def draw_food(main_window: Surface, food_pos: tuple[int, int], eaten_anim: int = 0) -> None:
    '''draw food'''
    if eaten_anim == 0:
        # pygame.draw.rect(main_window, white,
        #              pygame.Rect(food_pos[0], food_pos[1], SNAKE_SIZE, SNAKE_SIZE))
        pygame.draw.circle(main_window, white, (food_pos[0]+SNAKE_size/2, food_pos[1]+SNAKE_size/2), SNAKE_size/2, 0, True, True, True, True)
        #pygame.draw.circle(main_window, yellow, (food_pos[0]+SNAKE_SIZE/2, food_pos[1]+SNAKE_SIZE/2), SNAKE_SIZE/5, 0, True, True, True, True)

        return
    ampl = 1+0.3*eaten_anim
    # pygame.draw.rect(main_window, white, 
    #                  pygame.Rect(food_pos[0], food_pos[1], SNAKE_SIZE*ampl, SNAKE_SIZE*ampl))
    pygame.draw.circle(main_window, white, (food_pos[0]+SNAKE_size/2, food_pos[1]+SNAKE_size/2), SNAKE_size/2*ampl, 0, True, True, True, True)
    