from cs1robots import *
import time

create_world()

hubo = Robot()

def move_or_turn(robot : Robot):
    if robot.front_is_clear():
        robot.move()
    else:
        robot.turn_left()


print( bool(""))

hubo.move()
for _ in range(30):
    time.sleep(0.2)
    move_or_turn(hubo)


