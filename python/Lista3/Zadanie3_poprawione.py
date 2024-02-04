from collections import deque

def find_path(maze, start):
    rows, cols = len(maze), len(maze[0])
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    visited = set()
    start = tuple(start)
    
    queue = deque([(start, [start])])
    
    def is_valid(x, y):
        return 0 <= x < rows and 0 <= y < cols and maze[x][y] == ' '
    

    def get_neighbors(x, y):
        neighbors = []
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if is_valid(nx, ny) and (nx, ny) not in visited:
                neighbors.append((nx, ny))
        return neighbors
    
    while queue:
        (x, y), path = queue.popleft()
        
        if (x,y) != start and (x == 0 or y == 0 or x == rows - 1 or y == cols - 1):
            return path
        
        if (x, y) not in visited:
            visited.add((x, y))
            neighbors = get_neighbors(x, y)
            for neighbor in neighbors:
                new_path = path + [neighbor]
                queue.append((neighbor, new_path))
    
    return None




maze = [
    ['X', ' ', 'X', ' ', 'X', ' ', ' '],
    ['X', ' ', 'X', ' ', 'X', ' ', 'X'],
    ['X', ' ', ' ', ' ', ' ', ' ', ' '],
    ['X', 'X', ' ', 'X', 'X', 'X', 'X'],
    [' ', ' ', ' ', ' ', ' ', ' ', ' '],
    ['X', 'X', 'X', 'X', ' ', 'X', 'X']
]

start_point = (0, 1)
path = find_path(maze, start_point)

if path:
    print("Znaleziona ścieżka do wyjścia:")
    for x, y in path:
        print(f'({x}, {y})', end=' -> ')
    print("Wyjście")
else:
    print("Brak ścieżki do wyjścia.")
