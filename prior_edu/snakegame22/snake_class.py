"""
Snake class for inheritance
"""
from __future__ import annotations

import pygame

from snake_drawing import snake_draw_head, snake_draw_body, snake_draw_tail, SNAKE_size
from direction_class import Direction
from food_class import Food
from typing import overload, ClassVar, Generator

DELAY_ON_DEATH: int = 60
SNAKE_MOVING_FRAME: int = 4
'''SNAKE_MOVING_FRAME(기본값 = 4) 프레임 동안 SNAKE_SIZE 만큼 움직임'''

def SNAKE_size_move_skcl(d: int):
    global SNAKE_size
    SNAKE_size += d

class Snake:
    """Snake class 설명"""
    offset_x: ClassVar[int] = 0
    offset_y: ClassVar[int] = 0
    _dark_or_bright: ClassVar[int] = 1

    _main_window: ClassVar[pygame.Surface] = None
    _frame: ClassVar[tuple[int, int]] = None

    key_map: str = None
    '''기본값 None, 사용자지정 : 'asdf' or 'arrow' '''
    direction_current: ClassVar[Direction] = Direction.RIGHT
    direction_queue: ClassVar[list[Direction]] = []
    snake_list: ClassVar[list[type[Snake]]] = []

    def __init_subclass__(cls):
        '''subclass variable 독립화'''
        super().__init_subclass__()
        cls.snake_list = []
        cls.direction_queue = []

    def __init__(self, x: int, y: int, direc: Direction) -> None:
        '''add snake at exact position and direction'''
        self.x, self.y, self.direc = x, y, direc
        type(self).direction_current = direc
        type(self)._dark_or_bright *= -1
        self.after = None
        self.before = None
        self.is_dead: bool = False
        
        if len(type(self).snake_list)>0:
            _snake = type(self).snake_list[-1]
            self.before = _snake
            _snake.after = self
        type(self).snake_list.append(self)

        #drawing

        self._dark_or_bright: int = type(self)._dark_or_bright
        
        self.x_drawing_generator_object = self.x_drawing_generator()
        self.x_drawing: float = float(x)
        self.y_drawing_generator_object = self.y_drawing_generator()
        self.y_drawing: float = float(y)
    
    @property
    def pos(self) -> tuple[int, int]:
        '''Snake의 위치 (x, ys)'''
        return (self.x, self.y)
    
    @classmethod
    def head_pos(cls) -> int:
        '''Snake의 머리 좌표 [x, y] 반환'''
        if cls.snake_list:
            return cls.snake_list[-1].pos
        raise RuntimeError("called head_pos() where there are no instances of Snake")

    @classmethod
    def initialize_snake(cls, main_window: pygame.Surface, size:tuple[int, int], offset: tuple[int, int]) -> None:
        '''게임 시작 시의 Snake 설정'''
        cls._main_window = main_window
        cls._frame = size
        cls.offset_x, cls.offset_y = offset
        
    @classmethod
    def add_first_snake(cls, x: int, y: int, direc: Direction) -> None:
        '''처음 위치에 snake 생성'''
        cls(x + cls.offset_x, y + cls.offset_y, direc)
        #cls.print_snakes()

    @staticmethod
    def move_offset(dx: int = 0, dy: int = 0, move_snakes: bool = True) -> None:
        '''offset 이동'''
        Snake.offset_x += dx
        Snake.offset_y += dy
        if move_snakes:
            for snake in Snake.__subclasses__():
                snake.move_snake_by_offset(dx, dy)
    
    @classmethod
    def move_snake_by_offset(cls, dx, dy) -> None:
        '''offset에 따라 subclass 재설정'''
        for snake in cls.snake_list:
            snake.x += dx
            snake.y += dy
    
    @classmethod
    def set_offset(cls, x: int = 0, y: int = 0, move_snakes: bool = True) -> None:
        '''offset 설정'''
        cls.move_offset(x-cls.offset_x, y-cls.offset_y, move_snakes)

    @classmethod
    def set_frame(cls, x: int = 720, y: int = 480) -> None:
        '''frame 설정'''
        cls._frame = (x, y)
    
    @classmethod
    def move_frame(cls, dx: int = 720, dy: int = 480) -> None:
        '''frame 설정'''
        cls._frame = (dx + cls._frame[0], dy + cls._frame[1])

    @overload
    @classmethod
    def add(cls) -> None: ...
    @overload
    @classmethod
    def add(cls, direc: Direction) -> None: ...
    @overload
    @classmethod
    def add(cls, x: int, y: int, direc: Direction) -> None: ...
    @overload
    @classmethod
    def add(cls, snake: tuple[int, int, Direction]) -> None: ...

    @classmethod
    def add(cls, *args) -> None:
        '''새로운 Sanke 머리 생성'''
        if not cls.snake_list:
            raise RuntimeError("need at least one snake should exist. use add__first_snake()")
        if len(args) == 0:
            if cls.direction_queue:
                direc = cls.direction_queue.pop(0)
            else:
                direc = cls.direction_current
            cls.add(direc)
            return
        if len(args) == 3:
            x, y, direc = args
            cls(x, y, direc)
            return
        if len(args) == 1:
            arg = args[0]
            if isinstance(arg, tuple):
                cls(*arg)
                return
            if isinstance(arg, Direction):
                direc = arg
                _snake_before = cls.snake_list[-1]
                snake_pos = [_snake_before.x, _snake_before.y]
                vector = direc.to_vector()
                snake_pos[0] += vector[0]
                snake_pos[1] += vector[1]
                cls(*snake_pos, direc)
                return
        raise TypeError("Invalid arguments for add(): expected (x,y,direc), (snake_tuple,) or (direc,)")
    
    @classmethod
    def pop(cls) -> None:
        '''Snake 꼬리 제거'''
        if not cls.snake_list:
            raise IndexError("pop from enpty snake list")
        tail = cls.snake_list.pop(0)
        if cls.snake_list:
            cls.snake_list[0].before = None
        del tail
    
    @classmethod
    def get_keyboard(cls, key) -> None:
        '''키보드 입력 받기'''
        direc = Direction.get(key, key_map=cls.key_map)
        if direc != Direction.NOWHERE and cls.direction_current != direc.opposite():
            cls.direction_queue.append(direc)
            cls.direction_current = direc

    @classmethod
    def is_hit_itself(cls) -> bool:
        snake_pos = cls.head_pos()
        for block in cls.snake_list[:-1]:
            if snake_pos[0] == block.pos[0] and snake_pos[1] == block.pos[1]:
                return True
        return False

    @classmethod
    def is_hit_wall(cls) -> bool:
        snake_pos = cls.head_pos()
        if snake_pos[0] < cls.offset_x or snake_pos[0] > cls.offset_x + cls._frame[0] - SNAKE_size:
            return True
        if snake_pos[1] < cls.offset_y or snake_pos[1] > cls.offset_y + cls._frame[1] - SNAKE_size:
            return True
        return False

    @classmethod
    def print_snakes(cls) -> None:
        '''디버깅용'''
        print(len(cls.snake_list), 'snakes existing, head pos :', cls.head_pos())
    
    @classmethod
    def draw(cls, moving: bool = True) -> None:
        '''게임 화면에 Snake 그리기'''

        if not cls.snake_list:
            raise RuntimeError("there is no snake to draw")
        if not cls._main_window:
            raise RuntimeError("need to set game_window first using 'Snake.initialize_game()'")
        
        for snake in cls.snake_list:
            snake.draw_one(moving)
    
    def draw_one(self, moving: bool = True) -> None:
        '''Snake 하나 그린 후 Snake.before 그리기 호출'''
        if moving:
            self.drawing_next()

        if self is type(self).snake_list[-1]:
            snake_draw_head(self, type(self)._main_window)
        elif self is type(self).snake_list[0]:
            snake_draw_tail(self, type(self)._main_window)
        else:
            snake_draw_body(self, type(self)._main_window)
        
    @classmethod
    def game_over(cls) -> None:
        '''사망'''
        if not cls.snake_list:
            raise RuntimeError("there is no snake to draw")
        if not cls._main_window:
            raise RuntimeError("need to set game_window first using 'Snake.initialize_game()'")
        cls.snake_list[-1].die_and_next()
        del cls
    
    def die_and_next(self) -> None:
        '''죽이고 이미 죽어있으면 다음꺼 죽이기'''
        self.is_dead = True
        self.draw_one()
        pygame.display.update()
        pygame.time.delay(DELAY_ON_DEATH)
        if self.before:
            self.before.die_and_next()

    #these functions below are used for drawing snake

    def is_dark_or_bright(self) -> bool:
        '''returns whether snake is dark'''
        return self._dark_or_bright != type(self)._dark_or_bright

    def x_drawing_generator(self) -> Generator[float]:
        dx = self.direc.to_vector()[0]

        while True:
            for anim_frame in range(SNAKE_MOVING_FRAME-1, -1, -1):
                yield self.x-dx*anim_frame/SNAKE_MOVING_FRAME 
    
    def y_drawing_generator(self) -> Generator[float]:
        dy = self.direc.to_vector()[1]

        while True:
            for anim_frame in range(SNAKE_MOVING_FRAME-1, -1, -1):
                yield self.y-dy*anim_frame/SNAKE_MOVING_FRAME 

    def drawing_next(self) -> None:
        if self.is_dead:
            return
        
        x, y = next(self.x_drawing_generator_object), next(self.y_drawing_generator_object)
        self.x_drawing, self.y_drawing = x, y

    @staticmethod
    def snake_animation_delay() -> Generator[bool]:
        while True:
            yield True
            for _ in range(1, SNAKE_MOVING_FRAME):
                yield False

if __name__=='__main__':


    def asdf():
        i=0
        while True:
            yield (i*SNAKE_size, 0, Direction(1))
            i += 1

    qwer = asdf()

    
