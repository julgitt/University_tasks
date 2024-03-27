from time import time
from itertools import product
from random import randint
from typing import List, Tuple
import queue


# region Preprocessing
def preprocessing(maze_map: List[str], state: Tuple[List[Tuple[int, int]], str]):
    i = 0
    new_state = (state[0], state[1])
    while len(new_state[0]) > 2 and i < 4:
        new_state = preprocessed_moves(maze_map, new_state)
        i += 1

    if i == 4:
        preprocessing(maze_map, state)

    return new_state


def preprocessed_moves(maze_map: List[str], state: Tuple[List[Tuple[int, int]], str]):
    perms = list(product(['L', 'D', 'U', 'R'], repeat=4))

    min_state = (state[0], state[1])
    min_commanders = len(state[0])
    origin_state = (state[0], state[1])
    for perm in perms:
        for direction in perm:
            no_moves = False
            while not no_moves:
                if randint(0, 100) >= 85:
                    break
                no_moves, new_positions = move_all(maze_map, state[0], direction)
                if not no_moves:
                    state = update_state(state[1], new_positions, direction)

        new_commanders = len(state[0])
        moves = state[1]
        if (new_commanders == min_commanders and len(moves) < len(min_state[1])) or new_commanders < min_commanders:
            if len(moves) < 100:
                min_state = (state[0], moves)
                min_commanders = new_commanders
        state = origin_state
    return min_state


# endregion


# region BFS
def bfs(maze_map: List[str], state: Tuple[List[Tuple[int, int]], str],
        goals_positions: List[Tuple[int, int]]) -> Tuple[bool, str]:
    visited = {}
    q = queue.Queue()
    q.put(state)
    visited[tuple(state[0])] = True
    while not q.empty():
        current_state = q.get()
        if is_end_state(current_state, goals_positions):
            return True, current_state[1]
        for new_state in get_next_states(maze_map, current_state):
            pos = new_state[0]
            if tuple(pos) in visited:
                continue
            q.put(new_state)
            visited[tuple(pos)] = True
    return False, ""
# endregion


# region States and Movement
def update_state(commanders_moves_history: str,
                 new_positions: List[Tuple[int, int]], direction: str) -> Tuple[List[Tuple[int, int]], str]:
    commanders_moves_history += direction
    commanders_positions = new_positions
    return commanders_positions, commanders_moves_history


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


def move(x: int, y: int, direction: str) -> Tuple[int, int]:
    if direction == 'U':
        return x, y - 1
    elif direction == 'D':
        return x, y + 1
    elif direction == 'L':
        return x - 1, y
    elif direction == 'R':
        return x + 1, y


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


def solve():
    maze_map = load_maze('zad_input.txt')

    start_time = time()

    goals_positions = get_positions(maze_map, 'G')
    init_state = get_positions(maze_map, 'S'), ""
    preprocessed_state = preprocessing(maze_map, init_state)
    is_solution_found, result = bfs(maze_map, preprocessed_state, goals_positions)

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
