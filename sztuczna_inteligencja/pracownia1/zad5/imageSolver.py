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
            for _ in range(max_iterations):
                if choice([True, False]):
                    random_row_id = self.image.get_random_incorrect_row_id()
                    if random_row_id != -1:
                        self._handle_row(random_row_id)
                        continue
                    random_column_id = self.image.get_random_incorrect_column_id()
                    if random_column_id != -1:
                        self._handle_column(random_column_id)
                        continue
                else:
                    random_column_id = self.image.get_random_incorrect_column_id()
                    if random_column_id != -1:
                        self._handle_column(random_column_id)
                        continue
                    random_row_id = self.image.get_random_incorrect_row_id()
                    if random_row_id != -1:
                        self._handle_row(random_row_id)
                        continue

                return self.image.image

    def _handle_row(self, row_id: int) -> None:
        column_id = self.image.find_best_cell_in_row(row_id)
        self.image.swap_cell(row_id, column_id)

    def _handle_column(self, column_id: int) -> None:
        row_id = self.image.find_best_cell_in_column(column_id)
        self.image.swap_cell(row_id, column_id)
