from typing import List, Tuple
import queue


def update_state(commanders_moves_history: str,
                 new_positions: List[Tuple[int, int]], direction: str) -> Tuple[str, List[Tuple[int, int]]]:
    commanders_moves_history += direction
    commanders_positions = new_positions
    return commanders_moves_history, commanders_positions


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


def heuristic(state: Tuple[str, List[Tuple[int, int]]], distances: dict) -> int:
    return max(distances[commander] for commander in state[1]) + 1.01 * len(state[0])


def a_star(maze_map: List[str], state: Tuple[str, List[Tuple[int, int]]],
           goals_positions: List[Tuple[int, int]], distances: dict) -> Tuple[bool, str]:
    visited = set()
    q = queue.PriorityQueue()
    q.put((heuristic(state, distances), state))
    visited.add(tuple(state[1]))

    while not q.empty():
        _, current_state = q.get()
        if is_end_state(current_state, goals_positions):
            return True, current_state[0]
        for new_state in get_next_states(maze_map, current_state):
            pos = tuple(new_state[1])
            if pos not in visited:
                q.put((heuristic(new_state, distances), new_state))
                visited.add(pos)
    return False, ""


def get_next_states(maze_map: List[str], state: Tuple[str, List[Tuple[int, int]]]):
    new_states = []
    for direction in 'ULDR':
        no_moves, new_positions = move_all(maze_map, state[1], direction)
        if not no_moves:
            new_states.append(update_state(state[0], new_positions, direction))
    return new_states


def is_end_state(state: Tuple[str, List[Tuple[int, int]]], goals_positions: List[Tuple[int, int]]):
    for commander in state[1]:
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
    return no_moves, list(set(new_positions))


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


def main():
    maze_map = load_maze('zad_input.txt')
    height = len(maze_map)
    width = len(maze_map[0])
    goals_positions = get_positions(maze_map, 'G')
    distances = calculate_distances(maze_map, width, height, goals_positions)
    state = ("", get_positions(maze_map, 'S'))
    is_solution_found, result = a_star(maze_map, state, goals_positions, distances)
    with open("zad_output.txt", 'w') as file:
        if is_solution_found:
            print(result)
            print(result, file=file)


if __name__ == "__main__":
    main()
