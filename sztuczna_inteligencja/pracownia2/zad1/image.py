import itertools
from random import choice, randint
from typing import List


class Image:

    def __init__(self, height: int, width: int, columns_blocks: List[List[int]], rows_blocks: List[List[int]]):
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
        best_operations = float('inf')  # how many operations to correct
        best_cells = set  # column index of the best_cell

        if randint(0, 100) >= 55:
            return randint(0, self.width - 1)
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
        best_operations = float('inf')  # how many operations to correct
        best_cells = set  # column index of the best_cell

        if randint(0, 100) >= 55:
            return randint(0, self.height - 1)
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
    def _opt_dist(line: str, block_sizes: List[int]) -> int:
        memo = {}

        def rec(line: str, block_sizes: List[int]):
            try:
                return memo[(line, tuple(block_sizes))][0]
            except:
                min_operations = float('inf')
                best_mask = ''
                for i in range(len(line) - sum(block_sizes) - len(block_sizes) + 2):
                    mask = '.' * i + block_sizes[0] * '#'
                    if len(block_sizes) > 1:
                        mask += '.'
                        mask += rec(line[len(mask):], block_sizes[1:])
                    else:
                        mask += (len(line) - len(mask)) * '.'
                    operations = sum((a != b) for a, b in zip(line, mask))
                    if operations < min_operations:
                        min_operations = operations
                        best_mask = mask
                    if min_operations == abs(sum([int(i == '#') for i in line]) - sum(block_sizes)):
                        break
                memo[(line, tuple(block_sizes))] = (best_mask, min_operations)
                return best_mask

        rec(line, block_sizes)
        return memo[(line, tuple(block_sizes))][1]

    '''def _opt_dist(self, line: str, setup: List[int]):
        how_many = len(setup)
        length = len(line)

        def logical_xor(str1, str2):
            return bool(str1) ^ bool(str2)

        def check(choice):
            for idx, x in enumerate(choice):
                if x + setup[idx] > length:
                    return False
                if idx + 1 < how_many:
                    if x + setup[idx] + 1 > choice[idx + 1]:
                        return False
            return True

        def find_min(choice):
            temp_sum = 0
            for idx, x in enumerate(choice):
                temp_sum += logical_xor((1 if x == '#' else 0), (1 if line[idx] == '#' else 0))
            return temp_sum

        def generate_line(choice):
            new_line = ['.'] * length
            for idx, x in enumerate(choice):
                for i in range(setup[idx]):
                    new_line[x + i] = '#'
            return new_line

        poss_choices = itertools.combinations([x for x in range(0, length)], how_many)
        poss_choices = list(map(generate_line, filter(check, poss_choices)))
        # print(list(poss_choices))
        how_many_inv = list(map(find_min, poss_choices))
        # print(how_many_inv)
        min_inv = min(how_many_inv)
        # poss_choices = list(filter(lambda elem: how_many_inv[elem[0]] == min_inv, enumerate(poss_choices)))
        # rand_choice = random.choice(poss_choices)
        # return rand_choice[1]
        return min_inv'''
    # endregion
