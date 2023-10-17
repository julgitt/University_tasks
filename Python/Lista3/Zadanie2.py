from collections import deque

def find_path(maze, start):
    rows, cols = len(maze), len(maze[0])
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    visited = set()
    
    def is_valid(x, y):
        return 0 <= x < rows and 0 <= y < cols and maze[x][y] == ' '
    

    def get_neighbors(x, y):
        neighbors = []
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if is_valid(nx, ny) and (nx, ny) not in visited:
                neighbors.append((nx, ny))
        return neighbors
    

    start = tuple(start)
    end = (rows - 1, cols - 1)  # Zakładamy, że wyjście jest w prawym dolnym rogu labiryntu
    
    queue = deque([(start, [start])])
    
    while queue:
        (x, y), path = queue.popleft()
        
        if (x, y) == end:
            return path  # Znaleziono wyjście, zwracamy ścieżkę
        
        if (x, y) not in visited:
            visited.add((x, y))
            neighbors = get_neighbors(x, y)
            for neighbor in neighbors:
                new_path = path + [neighbor]
                queue.append((neighbor, new_path))
    
    return None  # Brak ścieżki do wyjścia




# Przykładowe użycie funkcji:
maze = [
    [' ', 'X', ' ', ' ', 'X', ' ', ' '],
    [' ', 'X', 'X', ' ', 'X', 'X', ' '],
    [' ', ' ', ' ', ' ', ' ', ' ', ' '],
    ['X', 'X', 'X', 'X', 'X', 'X', ' '],
    [' ', ' ', ' ', ' ', ' ', 'X', ' '],
    ['X', 'X', 'X', 'X', 'X', 'X', ' ']
]

start_point = (0, 0)
path = find_path(maze, start_point)

if path:
    print("Znaleziona ścieżka do wyjścia:")
    for x, y in path:
        print(f'({x}, {y})', end=' -> ')
    print("Wyjście")
else:
    print("Brak ścieżki do wyjścia.")