from typing import List

from image import Image
from random import choice


class ImageSolver:

    def __init__(self, height: int, width: int,
                 columns_blocks: List[List[int]], rows_blocks: List[List[int]]):
        self.columns_blocks = columns_blocks
        self.rows_blocks = rows_blocks
        self.image = Image(height, width, columns_blocks, rows_blocks)
        self.prev_operations = 0

    def solve(self, max_iterations: int) -> List[str]:
        while True:
            self.image.regenerate()
            for _ in range(max_iterations):
                random_row_id = self.image.get_random_incorrect_row_id()
                random_column_id = self.image.get_random_incorrect_column_id()
                rows_completed = (random_row_id == -1)
                cols_completed = (random_column_id == -1)
                if not rows_completed and (choice([True, False]) or cols_completed):
                    self._handle_row(random_row_id)
                elif not cols_completed:
                    self._handle_column(random_column_id)
                else:
                    return self.image.image

    def _handle_row(self, row_id: int) -> None:
        column_id = self.image.find_best_cell_in_row(row_id)
        self.image.swap_cell(row_id, column_id)

    def _handle_column(self, column_id: int) -> None:
        row_id = self.image.find_best_cell_in_column(column_id)
        self.image.swap_cell(row_id, column_id)
