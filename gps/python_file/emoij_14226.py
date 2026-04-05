from collections import deque

k = int(input())


length = round(1.5*k)
visited = bytearray([0]*length)


def bfs(start, visited):
    queue = deque([(start, 0, None)])
    visited[start] = 1

    while queue:

        #print(v, end=' ')
        v, count, copied = queue.popleft()

        if v==k:
            print(count)
            break
        
        #paste
        if copied:
            if v + copied < length:
                queue.append((v+copied, count+1, copied))
                visited[v + copied] = 1


        #copy
        if v != copied:
            if v*2 < length:
                queue.append((v, count+1, v))
            

        #v-1
        if 0<v-1 :
            if not visited[v-1]:
                queue.append((v-1, count+1, None))
                visited[v-1] = 1
        
        
                        




            

            

bfs(1, visited)
