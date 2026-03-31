class Robot():
    def __init__(self, beepers=0):
        self.beepers = beepers
        self.direction = 'north'
        self.position = [0, 0]
        self.beepers_loc = []
    
    def beepers_init(self, *locations):
        self.beepers_loc.extend(locations)

    def move(self):
        if self.direction == 'north':
            self.position[1] += 1
        elif self.direction == 'south':
            self.position[1] -= 1
        elif self.direction == 'east':
            self.position[0] += 1
        elif self.direction == 'west':
            self.position[0] -= 1
        print("Robot moves one step forward.")

    def turn_left(self):
        directions = ['north', 'west', 'south', 'east']
        current_index = directions.index(self.direction)
        self.direction = directions[(current_index + 1) % 4]
        print("Robot turns left 90 degrees.")
    
    def on_beeper(self):
        return tuple(self.position) in self.beepers_loc

    def pick_beeper(self):
        if self.on_beeper():
            self.beepers += 1
            self.beepers_loc.remove(tuple(self.position))
            print("Robot picks up a beeper.")
        else:
            print("No beepers to pick up.")

    def put_beeper(self):
        self.beepers -= 1
        self.beepers_loc.append(tuple(self.position))
        print("Robot puts down a beeper.")

    def end_program(self):
        print("Program ended.")
        print(f"Final position: {self.position}, Beepers: {self.beepers}")