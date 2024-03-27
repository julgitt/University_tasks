import heapq
from time import time
from typing import List, Tuple
import queue


# region Heuristic
def calculate_distances(maze_map: List[str], goals_positions: List[Tuple[int, int]]) -> dict:
    distances = {(y, x): float('inf') for x in range(len(maze_map[0])) for y in range(len(maze_map)) if maze_map[y][x] != '#'}
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
    return max(distances[commander] for commander in state[0]) + len(state[1])
# endregion


# region A*
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
# endregion


# region States and Movement
def get_next_states(maze_map: List[str], state: Tuple[List[Tuple[int, int]], str]):
    new_states = []
    for direction in 'ULDR':
        no_moves, new_positions = move_all(maze_map, state[0], direction)
        if not no_moves:
            new_states.append(update_state(state[1], new_positions, direction))
    return new_states


def update_state(commanders_moves_history: str,
                 new_positions: List[Tuple[int, int]], direction: str) -> Tuple[List[Tuple[int, int]], str]:
    commanders_moves_history += direction
    commanders_positions = new_positions
    return commanders_positions, commanders_moves_history


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


def move(x: int, y: int, direction: str) -> Tuple[int, int]:
    if direction == 'U':
        return x, y - 1
    elif direction == 'D':
        return x, y + 1
    elif direction == 'L':
        return x - 1, y
    elif direction == 'R':
        return x + 1, y
# endregion


# region Load Input Data
def load_maze(filename: str) -> List[str]:
    with open(filename, 'r') as file:
        return [line.strip().replace('\'', "") for line in file]


def get_positions(maze_map: List[str], symbol: str) -> List[Tuple[int, int]]:
    positions = []
    for y in range(len(maze_map)):
        for x in range(len(maze_map[0])):
            if maze_map[y][x] == symbol or maze_map[y][x] == 'B':
                positions.append((y, x))
    return positions
# endregion


def solve():
    maze_map = load_maze('zad_input.txt')

    start_time = time()

    goals_positions = get_positions(maze_map, 'G')
    init_state = get_positions(maze_map, 'S'), ""
    distances = calculate_distances(maze_map, goals_positions)
    is_solution_found, result = a_star(maze_map, init_state, goals_positions, distances)

    end_time = time()
    execution_time = end_time - start_time

    return is_solution_found, result, execution_time


def main():
    is_solution_found, result, execution_time = solve()
    with open("zad_output.txt", 'w') as file:
        if is_solution_found:
            print(result)
            print(result, file=file)

    with open("zad_time_output.txt", 'r') as time_file:
        data = time_file.readlines()

    if not data:
        data = [0.0, 0]

    with open("zad_time_output.txt", 'w') as time_file:
        time_file.write(f"{float(execution_time) + float(data[0])}\n{len(result) + int(data[1])}")

    print(f"Execution time: {execution_time} seconds. Path length: {len(result)}")


if __name__ == "__main__":
    main()
