from cs1robots import *
from typing import Tuple, List
import time

hubo : Robot = Robot(beepers=5)
hubo.direction = 'east'
#hubo.beepers_init((3, 0), (6, 0), (9, 0))
hubo.walls_init((3, 3), (3, 4), (3, 5), (3, 6),
                (4, 3), (5, 3), (6, 3),)

def dance():
    for i in range(4):
        hubo.turn_left(print_status=False)
        time.sleep(0.1)

def move_or_turn():
    if hubo.is_front_clear():
        hubo.move()
        if hubo.on_beeper():
            hubo.pick_beeper()
    else:
        hubo.turn_left()
        hubo.drop_beeper()

def mark_starting_point_and_move():
    hubo.drop_beeper()
    while not hubo.is_front_clear():
        hubo.turn_left()
    hubo.move()



#hubo moves counter-clockwise around the walls

mark_starting_point_and_move()



while not hubo.on_beeper():
    if hubo.is_right_clear():
        hubo.turn_right()
        hubo.move()
    elif hubo.front_is_clear():
        hubo.move()
    else:
        hubo.turn_left()
    time.sleep(0.2)


hubo.end_program()