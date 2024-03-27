import heapq
import time
from typing import List, Tuple
import queue


def update_state(commanders_moves_history: str,
                 new_positions: List[Tuple[int, int]], direction: str) -> Tuple[List[Tuple[int, int]], str]:
    commanders_moves_history += direction
    commanders_positions = new_positions
    return commanders_positions, commanders_moves_history


def calculate_distances(maze_map: List[str], width: int, height: int, goals_positions: List[Tuple[int, int]]) -> dict:
    distances = {(y, x): float('inf') for x in range(width) for y in range(height) if maze_map[y][x] != '#'}
    for goal_position in goals_positions:
        q = queue.Queue()
        q.put((goal_position, 0))
        visited = {goal_position}
        while not q.empty():
            position, depth = q.get()
            if depth < distances[position]:
                distances[position] = depth
            y, x = position
            for neighbour in [(y - 1, x), (y + 1, x), (y, x - 1), (y, x + 1)]:
                y, x = neighbour
                if maze_map[y][x] != '#' and neighbour not in visited:
                    q.put((neighbour, depth + 1))
                    visited.add(neighbour)
    return distances


def heuristic(state: Tuple[List[Tuple[int, int]], str], distances: dict) -> int:
    return 4 * max(distances[commander] for commander in state[0]) + len(state[1])


def a_star(maze_map: List[str], state: Tuple[List[Tuple[int, int]], str],
           goals_positions: List[Tuple[int, int]], distances: dict) -> Tuple[bool, str]:
    visited = set()
    q = []
    heapq.heappush(q, (heuristic(state, distances), state))
    visited.add(tuple(state[0]))

    while len(q) > 0:
        _, current_state = heapq.heappop(q)
        if is_end_state(current_state, goals_positions):
            return True, current_state[1]
        for new_state in get_next_states(maze_map, current_state):
            pos = tuple(new_state[0])
            if pos not in visited:
                heapq.heappush(q, (heuristic(new_state, distances), new_state))
                visited.add(pos)
    return False, ""


def get_next_states(maze_map: List[str], state: Tuple[List[Tuple[int, int]], str]):
    new_states = []
    for direction in 'ULDR':
        no_moves, new_positions = move_all(maze_map, state[0], direction)
        if not no_moves:
            new_states.append(update_state(state[1], new_positions, direction))
    return new_states


def is_end_state(state: Tuple[List[Tuple[int, int]], str], goals_positions: List[Tuple[int, int]]):
    for commander in state[0]:
        if commander not in goals_positions:
            return False
    return True


def move_all(maze_map: List[str], commanders_positions: List[Tuple[int, int]],
             direction: str) -> Tuple[bool, List[Tuple[int, int]]]:
    new_positions = []
    no_moves = True
    for y, x in commanders_positions:
        new_x, new_y = move(x, y, direction)
        if maze_map[new_y][new_x] != '#':
            new_positions.append((new_y, new_x))
            no_moves = False
        else:
            new_positions.append((y, x))
    return no_moves, sorted(list(set(new_positions)))


def move(x, y, direction):
    if direction == 'U':
        return x, y - 1
    elif direction == 'D':
        return x, y + 1
    elif direction == 'L':
        return x - 1, y
    elif direction == 'R':
        return x + 1, y


def load_maze(filename):
    with open(filename, 'r') as file:
        return [line.strip().replace('\'', "") for line in file]


def get_positions(maze_map: List[str], symbol: str) -> List[Tuple[int, int]]:
    positions = []
    for y in range(len(maze_map)):
        for x in range(len(maze_map[0])):
            if maze_map[y][x] == symbol or maze_map[y][x] == 'B':
                positions.append((y, x))
    return positions


def solve():
    maze_map = load_maze('zad_input.txt')
    height = len(maze_map)
    width = len(maze_map[0])
    start = time.time()
    goals_positions = get_positions(maze_map, 'G')
    distances = calculate_distances(maze_map, width, height, goals_positions)
    state = (get_positions(maze_map, 'S'), "")
    is_solution_found, result = a_star(maze_map, state, goals_positions, distances)
    end = time.time()
    return end - start

def main():
    maze_map = load_maze('zad_input.txt')
    height = len(maze_map)
    width = len(maze_map[0])
    start = time.time()
    goals_positions = get_positions(maze_map, 'G')
    distances = calculate_distances(maze_map, width, height, goals_positions)
    state = (get_positions(maze_map, 'S'), "")
    is_solution_found, result = a_star(maze_map, state, goals_positions, distances)
    end = time.time()
    with open("zad_output.txt", 'w') as file:
        if is_solution_found:
            print(f"{end - start} \n{result}")
            print(result, file=file)

    f_in = open("zad_input.txt", 'r', encoding="utf8")
    f_in_temp = open("zad4_output.txt", 'r', encoding="utf8")
    data = f_in_temp.readlines()
    if data == []:
        data = [0, 0]
    f_in_temp.close()
    f_out = open("zad4_output.txt", 'w', encoding="utf8")
    for line, d in zip(solve(f_in.readlines()), data):
        f_out.write(str(float(line) + float(d)) + '\n')


if __name__ == "__main__":
    main()
