from typing import List
from imageSolver import ImageSolver


class Puzzle:
    def __init__(self, width: int, height: int, rows: List[int], columns: List[int]):
        self.width = width
        self.height = height
        self.rows = rows
        self.columns = columns

    @classmethod
    def from_file(cls, file_path: str) -> 'Puzzle':
        with open(file_path, 'r') as file:
            width, height = map(int, file.readline().split())
            rows = [int(file.readline()) for _ in range(height)]
            columns = [int(file.readline()) for _ in range(width)]
        return cls(width, height, rows, columns)

    def solve_puzzle(self, output_file: str, iterations: int = 500) -> None:
        solver = ImageSolver(self.height, self.width, self.columns, self.rows)
        with open(output_file, "w", encoding='utf-8') as output_file:
            for line in solver.solve(iterations):
                output_file.write(line + '\n')


def main():
    puzzle = Puzzle.from_file("zad5_input.txt")
    puzzle.solve_puzzle("zad5_output.txt")


if __name__ == "__main__":
    main()
