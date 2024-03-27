from random import choice

from image import Image


def solve(max_iterations: int, rows, columns) -> List[str]:
    image = Image(len(rows), len(columns), columns, rows)
    prev_operations = 0
    while True:
        image.regenerate()
        for _ in range(max_iterations):
            random_row_id = image.get_random_incorrect_row_id()
            random_column_id = image.get_random_incorrect_column_id()
            rows_completed = (random_row_id == -1)
            cols_completed = (random_column_id == -1)
            if not rows_completed and (choice([True, False]) or cols_completed):
                _handle_row(random_row_id)
            elif not cols_completed:
                _handle_column(random_column_id)
            else:
                return image.image


def _handle_row(self, row_id: int) -> None:
    column_id = self.image.find_best_cell_in_row(row_id)
    self.image.swap_cell(row_id, column_id)


def _handle_column(self, column_id: int) -> None:
    row_id = self.image.find_best_cell_in_column(column_id)
    self.image.swap_cell(row_id, column_id)


def main():
    iterations = 500

    with open("zad_input.txt", 'r') as file:
        height, width = map(int, file.readline().split())
        rows = [list(map(int, file.readline().strip().split())) for _ in range(height)]
        columns = [list(map(int, file.readline().strip().split())) for _ in range(width)]

    with open("zad_output.txt", "w", encoding='utf-8') as output_file:
        for line in solve(iterations * width * height):
            output_file.write(line + '\n')


if __name__ == "__main__":
    main()
