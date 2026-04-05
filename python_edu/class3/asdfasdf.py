import math
from cs1robots import *
import time


create_world(avenues=12, streets=12)

hubo = Robot()
hubo._refresh()
for _ in range(4):
    hubo.move()
    hubo._refresh()
    time.sleep(0.5)
    
