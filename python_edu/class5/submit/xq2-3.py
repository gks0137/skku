M = int(input())
lst = []
x, y = 1, 0
direc = [0, 1]

def spiral() -> tuple[int, int]:
    def is_out_of_range(pos):
        for what in pos:
            if pos[0] + M * (pos[1] - 1) in lst or what < 1 or M < what:
                return True
        return False
    
    def go(x, y, direc):
        return (x + direc[0], y + direc[1])
    
    def turn():
        if direc[0]:
            direc[1] = -direc[0]
            direc[0] = 0
        else:
            direc[0] = direc[1]
            direc[1] = 0

    if is_out_of_range(go(x, y, direc)):
        turn()
    return go(x, y, direc)

for _ in range(M * M):
    x, y = spiral()
    lst.append(x + M * (y - 1))

print(*lst)

