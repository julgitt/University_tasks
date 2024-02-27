from typing import List

from imageSolver import ImageSolver


WIDTH: int
HEIGHT: int
ROWS: List[int]
COLUMNS: List[int]

#region Input
def load_input_from_file() -> None:
    global WIDTH, HEIGHT, ROWS, COLUMNS
    with open("zad5_input.txt", 'r') as file:
        WIDTH, HEIGHT = map(int, file.readline().split())
        ROWS = [int(file.readline()) for _ in range(HEIGHT)]
        COLUMNS = [int(file.readline()) for _ in range(WIDTH)]
#endregion

#region Main
def main():
    load_input_from_file()
    solver = ImageSolver(HEIGHT, WIDTH, COLUMNS, ROWS)
    with open("zad5_output.txt", "w", encoding='utf-8') as output_file:
        for line in solver.solve(500):
            output_file.write(line + '\n')


if __name__ == "__main__":
    main()
#endregion