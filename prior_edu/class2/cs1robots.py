from typing import Tuple, List

class Robot():
    '''
    A simple robot class with wall detection capability.

    Attributes:
        beepers (int): Number of beepers the robot has.
    '''

    def __init__(self, beepers: int = 0) -> None:
        '''
        Docstring for __init__
        
        :param self: The robot instance
        :param beepers: The initial number of beepers the robot has
        :type beepers: int
        '''
        self.beepers = beepers
        self.direction = 'north'
        self.position = [0, 0]
        self.beepers_loc = set()
        self.walls = set()
    
    def beepers_init(self, *locations : Tuple[int, int]) -> None:
        '''
        Initialize beeper locations
        
        :param self: The robot instance
        :param locations: A list of tuples representing beeper locations
        :type locations: Tuple[int, int]
        :return: None
        :rtype: None
        '''
        self.beepers_loc = set(map(tuple,locations))

    def walls_init(self, *walls : Tuple[int, int]) -> None:
        '''
        Initialize wall locations

        :param self: The robot instance
        :param walls: A list of tuples representing wall locations
        :type walls: Tuple[int, int]
        :return: None
        :rtype: None
        '''
        self.walls = set(map(tuple,walls))

    def next_position(self) -> Tuple[int, int]:
        '''
        return the next position based on current direction
        
        :param self: The robot instance
        :return: The next position as a tuple of integers (x, y)
        :rtype: Tuple[int, int]
        '''
        next_position = list(self.position)
        if self.direction == 'north':
            next_position[1] += 1
        elif self.direction == 'south':
            next_position[1] -= 1
        elif self.direction == 'east':
            next_position[0] += 1
        elif self.direction == 'west':
            next_position[0] -= 1
        return tuple(next_position)

    def is_front_clear(self) -> bool:
        '''
        return whether the front is clear (no wall and within bounds)
        
        :param self: The robot instance
        :return: boolean indicating if the front is clear
        :rtype: bool
        '''
        next_position = self.next_position()
        return (next_position not in self.walls) and (0 <= next_position[0] < 7) and (0 <= next_position[1] < 7)

    def is_right_clear(self) -> bool:
        '''
        return whether the right side is clear (no wall and within bounds)
        
        :param self: The robot instance
        :return: boolean indicating if the right side is clear
        :rtype: bool
        '''
        original_direction = self.direction
        self.turn_right(print_status=False)
        right_clear = self.is_front_clear()
        # Restore original direction
        self.direction = original_direction
        return right_clear

    def move(self) -> None:
        '''
        Move the robot one step forward if the front is clear
        
        :param self: The robot instance
        :return: None
        :rtype: None
        '''
        if not self.is_front_clear():
            print("Move blocked by a wall.")
            return
        self.position = list(self.next_position())
        print("Robot moves one step forward.")

    def turn_left(self, print_status : bool = True) -> None:
        '''
        Turn the robot left 90 degrees
        
        :param self: The robot instance
        :param print_status: Whether to print a message about the turn
        :return: None
        :rtype: None
        '''
        directions = ['north', 'west', 'south', 'east']
        current_index = directions.index(self.direction)
        self.direction = directions[(current_index + 1) % 4]
        if print_status:
            print("Robot turns left 90 degrees.")
    
    def turn_right(self, print_status : bool = True) -> None:
        '''
        Turn the robot right 90 degrees
        
        :param self: The robot instance
        :param print_status: Whether to print a message about the turn
        :return: None
        :rtype: None
        '''
        for _ in range(3):
            self.turn_left(print_status=False)
        if print_status:
            print("Robot turns right 90 degrees.")

    def on_beeper(self) -> bool:
        '''
        Check if the robot is on a beeper
        
        :param self: The robot instance
        :return: boolean indicating if the robot is on a beeper
        :rtype: bool
        '''
        return tuple(self.position) in self.beepers_loc

    def pick_beeper(self) -> None:
        '''
        Pick up a beeper if the robot is on one
        
        :param self: The robot instance
        :return: None
        :rtype: None
        '''
        if self.on_beeper():
            self.beepers += 1
            self.beepers_loc.remove(tuple(self.position))
            print("Robot picks up a beeper.")
        else:
            print("No beepers to pick up.")

    def drop_beeper(self) -> None:
        '''
        Drop a beeper at the current position
        
        :param self: The robot instance
        :return: None
        :rtype: None
        '''
        if self.on_beeper():
            print("There is already a beeper here.")
            return
        self.beepers -= 1
        self.beepers_loc.add(tuple(self.position))
        print("Robot puts down a beeper.")




    def end_program(self):
        '''
        End the program and print final status
        
        :param self: The robot instance
        :return: None
        :rtype: None
        '''
        print("Program ended.")
        print(f"Final position: {self.position}, Beepers: {self.beepers}")





if __name__ == "__main__":    # Simple test
    r = Robot(beepers=3)
    r.walls_init((1,0), (1,1), (1,2))
    r.beepers_init((0,1), (2,2))
    r.move()
    r.pick_beeper()
    r.turn_left()
    r.move()
    r.move()
    r.drop_beeper()
    r.end_program()