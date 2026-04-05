import heapq

# 1. 휴리스틱 함수: 현재 위치에서 목표까지의 예상 거리 (맨해튼 거리 사용)
def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

def a_star(maze, start, end):
    rows, cols = len(maze), len(maze[0])
    
    # 2. 우선순위 큐 (Open List): (f_score, 현재 좌표) 저장
    open_list = []
    heapq.heappush(open_list, (0, start))
    
    # 3. 경로 추적 및 비용 관리를 위한 사전(dict)
    came_from = {}  # 어디서 왔는지 기록 (경로 복원용)
    g_score = {start: 0}  # 시작점에서 현재까지의 실제 비용
    
    while open_list:
        # f_score가 가장 낮은 노드를 꺼냄
        current_f, current = heapq.heappop(open_list)
        
        # 목표 도달 시 경로 복원
        if current == end:
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            return path[::-1] # 역순으로 저장된 경로를 뒤집어서 반환

        # 상하좌우 인접 노드 탐색
        for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            neighbor = (current[0] + dx, current[1] + dy)
            
            # 맵 범위 내에 있고 벽(1)이 아닌 경우만 탐색
            if 0 <= neighbor[0] < rows and 0 <= neighbor[1] < cols:
                if maze[neighbor[0]][neighbor[1]] == 1:
                    continue
                
                # 가상의 새로운 g_score 계산 (이동 비용은 1로 가정)
                tentative_g_score = g_score[current] + 1
                
                # 더 짧은 경로를 찾은 경우 정보 업데이트
                if neighbor not in g_score or tentative_g_score < g_score[neighbor]:
                    came_from[neighbor] = current
                    g_score[neighbor] = tentative_g_score
                    f_score = tentative_g_score + heuristic(neighbor, end)
                    heapq.heappush(open_list, (f_score, neighbor))
                    
    return None # 경로를 찾을 수 없는 경우

# --- 테스트 실행 ---
# 0: 이동 가능, 1: 벽(장애물)
maze = [
    [0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0],
    [0, 0, 0, 1, 0],
    [1, 1, 0, 0, 0],
    [0, 0, 0, 0, 0]
]

start, end = (0, 0), (4, 4)
result_path = a_star(maze, start, end)

if result_path:
    print(f"최단 경로 발견: {result_path}")
else:
    print("경로를 찾을 수 없습니다.")
