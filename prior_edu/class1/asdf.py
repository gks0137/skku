def print_message():
    print("This is a sample function in asdf.py")
    print("SKKU is fantastic!")

def repeat_message(times):
    #list(map(lambda x: print_message(), range(times)))

    for _ in range(times):
        print_message()

repeat_message2 = lambda times: [print_message() for _ in range(times)]

#repeat_message(2)

repeat_message2(times=2)


'''
from cs1robots import *

#create a robot with one beeper
hubo = Robot(beepers=1)

#move one step forward 
hubo.move()

#turn left 90 degrees
hubo.turn_left()

hubo.move()

#how can hubo turn right?
hubo.turn_right = lambda: [hubo.turn_left() for _ in range(3)]
hubo.turn_right()

hubo.move()

'''