from cs1media import *


red = (255, 0, 0)
blue = (0, 0, 255)
green = (0, 255, 0)
yellow = (255, 255, 0)
black = (0, 0, 0)
purple = (255, 0, 255)
yellow = (255, 255, 0)
white = (255, 255, 255)

img = create_picture(400, 400, purple)
w, h = img.size()

for i in range(w):
    img.set(i, h/5, yellow)
    img.set(i, h/5-1, yellow)
    img.set(i, h/5+1, yellow)

img.show()