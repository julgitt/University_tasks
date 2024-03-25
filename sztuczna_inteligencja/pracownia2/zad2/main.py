from typing import List, Tuple
from random import randint
from itertools import product
import queue
import time


class State:
    def __init__(self, commanders_moves_history: str,
                 commanders_positions: List[Tuple[int, int]]):
        self.commanders_moves_history = commanders_moves_history
        self.commanders_positions = commanders_positions

    def update(self, new_positions: List[Tuple[int, int]], direction: str):
        self.commanders_moves_history += direction
        self.commanders_positions = new_positions


class Maze:
    def __init__(self, maze_map: List[str]):
        self.map: List[str] = maze_map
        self.height: int = len(maze_map)
        self.width: int = len(maze_map[0])
        self.state: State = State("", self.get_start_positions())

    def get_start_positions(self) -> List[Tuple[int, int]]:
        starts = []
        for y in range(self.height):
            for x in range(self.width):
                if self.map[y][x] in ('S', 'B'):
                    starts.append((x, y))
        return starts

    # region Main Logic
    def search_winning_plan(self):
        origin_state = State(self.state.commanders_moves_history, self.state.commanders_positions)

        i = 0
        while len(self.state.commanders_positions) > 2 and i < 4:
            self.preprocessed_moves()
            i += 1

        if i == 4:
            self.state = origin_state
            self.search_winning_plan()

        # print(self.state.commanders_moves_history)
        # print(len(self.state.commanders_positions))
        if self.bfs():
            return True, self.state.commanders_moves_history
        return False, ''

    # region Commanders Preprocessing Tactic
    def preprocessed_moves(self):
        perms = list(product(['L', 'D', 'U', 'R'], repeat=4))

        min_state = self.state
        min_commanders = len(self.state.commanders_positions)
        origin_state = State(self.state.commanders_moves_history, self.state.commanders_positions)
        for perm in perms:
            for direction in perm:
                no_moves = False
                while not no_moves:
                    if randint(0, 100) >= 85:
                        break
                    no_moves, new_positions = self.move_all(direction)
                    if not no_moves:
                        self.state.update(new_positions, direction)

            new_commanders = len(self.state.commanders_positions)
            if new_commanders < min_commanders:
                if len(self.state.commanders_moves_history) < 100:
                    min_state = State(self.state.commanders_moves_history, self.state.commanders_positions)
                    min_commanders = new_commanders
            self.state = origin_state
        self.state = min_state
    # endregion

    # region BFS
    def bfs(self):
        visited = {}
        q = queue.Queue()
        q.put(self.state)
        visited[tuple(self.state.commanders_positions)] = True
        while not q.empty():
            self.state = q.get()
            if self.is_end_state():
                return True
            for new_state in self.get_next_states():
                pos = new_state.commanders_positions
                if tuple(pos) in visited:
                    continue
                q.put(new_state)
                visited[tuple(pos)] = True
        return False

    def get_next_states(self):
        new_states = []
        for direction in ['U', 'L', 'D', 'R']:
            no_moves, new_positions = self.move_all(direction)
            if not no_moves:
                new_state = State(self.state.commanders_moves_history, self.state.commanders_positions)
                new_state.update(new_positions, direction)
                new_states.append(new_state)
        return new_states

    def is_end_state(self):
        for x, y in self.state.commanders_positions:
            if self.map[y][x] not in ('G', 'B'):
                return False
        return True
    # endregion

    # region Moving
    def move_all(self, direction):
        new_positions = []
        no_moves = True
        for x, y in self.state.commanders_positions:
            new_x, new_y = self.move(x, y, direction)
            if self.map[new_y][new_x] != '#':
                new_positions.append((new_x, new_y))
                no_moves = False
            else:
                new_positions.append((x, y))

        unique_positions = []
        for pos in new_positions:
            if pos not in unique_positions:
                unique_positions.append(pos)

        return no_moves, unique_positions

    @staticmethod
    def move(x, y, direction):
        if direction == 'U':
            return x, y - 1
        elif direction == 'D':
            return x, y + 1
        elif direction == 'L':
            return x - 1, y
        elif direction == 'R':
            return x + 1, y
    # endregion

    # region Debugging
    def print_maze(self):
        print(self.state.commanders_moves_history)
        print()
        y = 0
        for line in self.map:
            x = 0
            for element in line:
                if (x, y) in self.state.commanders_positions:
                    if element == 'G' or element == 'B':
                        print('B', end=" ")
                    else:
                        print('S', end=" ")
                elif element == 'S':
                    print(' ', end=" ")
                elif element == 'B':
                    print('G', end=" ")
                else:
                    print(element, end=" ")
                x += 1
            y += 1
            print()

        print()
        print()
        print()
    # endregion


def load_maze(filename):
    with open(filename, 'r') as file:
        return [line.strip().replace('\'', "") for line in file]


def main():

    maze = Maze(load_maze('zad_input.txt'))
    start_time = time.time()
    is_solution_found, history = maze.search_winning_plan()
    end_time = time.time()
    with open("zad_output.txt", 'w') as file:
        if is_solution_found:
            print(history)
            file.write(history)

    execution_time = end_time - start_time
    print(f"Execution time: {execution_time} seconds. Path length: {len(history)}")

if __name__ == "__main__":
    main()
