from typing import List

from image import Image
from random import choice


class ImageSolver:

    def __init__(self, height: int, width: int,
                 columns_blocks: List[int], rows_blocks: List[int]):
        self.columns_blocks = columns_blocks
        self.rows_blocks = rows_blocks
        self.image = Image(height, width, columns_blocks, rows_blocks)
        self.prev_operations = 0

    def solve(self, max_iterations: int) -> List[str]:
        while True:
            self.image.regenerate()
            cols_solved = False
            rows_solved = False
            for _ in range(max_iterations):
                if not rows_solved and choice([True, False]):
                    random_row_id = self.image.get_random_incorrect_row_id()
                    rows_solved = random_row_id == -1
                    if not rows_solved:
                        self._handle_row(random_row_id)
                elif not cols_solved:
                    random_column_id = self.image.get_random_incorrect_column_id()
                    cols_solved = random_column_id == -1
                    if not cols_solved:
                        self._handle_column(random_column_id)
                else:
                    return self.image.image

    def _handle_row(self, row_id: int) -> None:
        column_id = self.image.find_best_cell_in_row(row_id)
        self.image.swap_cell(row_id, column_id)

    def _handle_column(self, column_id: int) -> None:
        row_id = self.image.find_best_cell_in_column(column_id)
        self.image.swap_cell(row_id, column_id)
