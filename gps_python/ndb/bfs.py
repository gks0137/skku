from collections import deque

n, k = map(int, input().split())


length = round(1.5*k)
visited = [False] * length
visit_where = deque([n])

def end(visited):
    visit_where = deque([k])
    where = k
    while where != n:
        where = visited[where]
        visit_where.append((where))
    
    c = len(visit_where)
    print(c-1)

    for _ in range(c):
        print(visit_where.pop(), end=' ')


def bfs(start, visited):
    visited[start] = start
    queue = deque([start])
    

    while queue:
        v = queue.popleft()
        #print(v, end=' ')
       

        for i in [2*v, v-1, v+1]:
            if 2*v<0 or length<=i:
                continue

            if visited[i] == False:
                queue.append(i)
                visited[i] = v

                if i == k:
                    end(visited)
                    break
        else:
            continue
        break

if k<=n:
    print(n-k)
    visit_where = list(range(k, n+1))
    visit_where.reverse()

    print(*visit_where)
else:
    bfs(n, visited)
