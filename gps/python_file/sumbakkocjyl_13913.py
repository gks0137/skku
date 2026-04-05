from collections import deque

n, k = map(int, input().split())


length = round(1.51*k)
visited = [-1] * length

def end(visited):
    where = k
    c = 0
    next = None
    while where != n:
        before = visited[where]
        visited[where] = next
        next = where
        where = before
        c += 1


    visited[where] = next
    
    print(c)

    where = n
    while where != k:
        print(where, end=' ')
        where = visited[where]
    print(where)


def bfs(start, visited):
    visited[start] = start
    queue = deque([start])
    

    while queue:
        v = queue.popleft()
        #print(v, end=' ')
       

        for i in [2*v, v-1, v+1]:
            if i<0 or length<=i:
                continue

            if visited[i] == -1:
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
