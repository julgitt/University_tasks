from random import choice, randint
from typing import List


class Image:

    def __init__(self, height: int, width: int, columns_blocks: List[int], rows_blocks: List[int]):
        self.height = height
        self.width = width
        self.columns_blocks = columns_blocks
        self.rows_blocks = rows_blocks
        self.image = []
        self.rotated_image = []

    # region Getters
    def _get_row(self, index: int) -> str:
        return self.image[index]

    def _get_column(self, index: int) -> str:
        return self.rotated_image[index]

    # endregion

    # region Image Update
    def swap_cell(self, row_id: int, col_id: int) -> None:
        row = self.image[row_id]
        current_char = row[col_id]
        new_char = '#' if current_char == '.' else '.'
        self.image[row_id] = row[:col_id] + new_char + row[col_id + 1:]
        self._update_rotated_image()

    def regenerate(self) -> None:
        self.image = []
        for _ in range(self.height):
            self.image.append(''.join(choice('.#') for _ in range(self.width)))
        self._update_rotated_image()

    def _update_rotated_image(self) -> None:
        self.rotated_image = []
        for i in range(self.width):
            self.rotated_image.append("".join([line[i] for line in self.image]))

    # endregion

    # region Incorrect Lines Getters
    def get_random_incorrect_row_id(self) -> int:
        incorrect_rows = [i for i in range(self.height) if self._opt_dist(self._get_row(i), self.rows_blocks[i]) > 0]
        return choice(incorrect_rows) if incorrect_rows else -1

    def get_random_incorrect_column_id(self) -> int:
        incorrect_columns = [i for i in range(self.width) if
                             self._opt_dist(self._get_column(i), self.columns_blocks[i]) > 0]
        return choice(incorrect_columns) if incorrect_columns else -1

    # endregion

    # region Find Best Pick
    def find_best_cell_in_row(self, row_id: int) -> int:
        best_operations = self.width * self.height  # how many operations to correct
        best_cells = set  # column index of the best_cell

        if randint(0, 100) >= 99:
            return randint(0, self.width)
        for col_id in range(0, self.width):
            self.swap_cell(row_id, col_id)
            current_operations = self._opt_dist(self._get_row(row_id), self.rows_blocks[row_id])
            for i in range(self.width):
                current_operations += self._opt_dist(self._get_column(i), self.columns_blocks[i])
            if current_operations < best_operations:
                best_operations = current_operations
                best_cells = {col_id}
            elif current_operations == best_operations:
                best_cells.add(col_id)
            self.swap_cell(row_id, col_id)

        return choice(list(best_cells))

    def find_best_cell_in_column(self, col_id: int) -> int:
        best_operations = self.width * self.height  # how many operations to correct
        best_cells = set  # column index of the best_cell

        if randint(0, 100) >= 99:
            return randint(0, self.height)
        for row_id in range(0, self.height):
            self.swap_cell(row_id, col_id)
            current_operations = self._opt_dist(self._get_column(col_id), self.columns_blocks[col_id])
            for i in range(self.height):
                current_operations += self._opt_dist(self._get_row(i), self.rows_blocks[i])
            if current_operations < best_operations:
                best_operations = current_operations
                best_cells = {row_id}
            elif current_operations == best_operations:
                best_cells.add(row_id)
            self.swap_cell(row_id, col_id)

        return choice(list(best_cells))

    @staticmethod
    def _opt_dist(line: str, block_size: int) -> int:
        min_operations = float('inf')

        for i in range(len(line) - block_size + 1):
            operations = line.count('#', 0, i) \
                         + line.count('.', i, i + block_size) \
                         + line.count('#', block_size + i, len(line))
            if min_operations > operations:
                min_operations = operations

        return min_operations
    # endregion
