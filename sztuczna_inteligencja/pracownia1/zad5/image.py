from copy import copy, deepcopy
from random import choice
from typing import List, Tuple

class Image:
    
    def __init__(self, height: int, width: int, columns_blocks: List[int], rows_blocks: List[int]):
        self.height = height
        self.width = width
        self.columns_blocks = columns_blocks
        self.rows_blocks = rows_blocks
        self.image = []
        self.rotated_image = []
    
    #region Getters
    def _get_row(self, index: int) -> List[str]:
        return self.image[index]

    def _get_column(self, index: int) -> List[str]:
        return self.rotated_image[index]
    #endregion
    
    #region Image Update   
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
    
    #endregion
    
    #region Incorrect Lines Getters     
    def get_random_incorrect_row_id(self) -> int:
        incorrect_rows = [i for i in range(self.height) if self._opt_dist(self._get_row(i), self.rows_blocks[i]) > 0]
        return choice(incorrect_rows) if incorrect_rows else -1

    def get_random_incorrect_column_id(self) -> int:
        incorrect_columns = [i for i in range(self.width) if self._opt_dist(self._get_column(i), self.columns_blocks[i]) > 0]
        return choice(incorrect_columns) if incorrect_columns else -1
    #endregion
    
    #region Find Best Pick
    def find_best_cell_in_row(self, row_id: int) -> Tuple[int, int]:
        best_opers = 100   # how many operations to correct 
        best_cell = 0      # column index of the best_cell
        
        for col_id in range(0, self.width):
            img_copy = deepcopy(self)
            img_copy.swap_cell(row_id, col_id)
            current_opers = img_copy._opt_dist(img_copy._get_row(row_id), img_copy.rows_blocks[row_id])
            for i in range(img_copy.width):
                current_opers += img_copy._opt_dist(img_copy._get_column(i), img_copy.columns_blocks[i])
            if current_opers < best_opers:
                best_opers = current_opers
                best_cell = col_id
                
        return best_cell
    
    def find_best_cell_in_column(self, col_id: int) -> Tuple[int, int]:
        best_opers = 100  # how many operations to correct 
        best_cell = 0     # column index of the best_cell
        
        for row_id in range(0, self.height):
            img_copy = deepcopy(self)
            img_copy.swap_cell(row_id, col_id)
            current_opers = img_copy._opt_dist(img_copy._get_column(col_id), img_copy.columns_blocks[col_id])
            for i in range(img_copy.height):
                current_opers += img_copy._opt_dist(img_copy._get_row(i), img_copy.rows_blocks[i])
            if current_opers < best_opers:
                best_opers = current_opers
                best_cell = row_id
                
        return best_cell
    
    def _opt_dist(self, line: str, block_size: int) -> int:
        min_operations = float('inf')
        
        for i in range(len(line) - block_size + 1):
            operations = line.count('#', 0, i) \
                        + line.count('.', i, i + block_size) \
                        + line.count('#', block_size + i, len(line))
            if min_operations > operations: 
                min_operations = operations
                
        return min_operations
    #endregion
    
    #region Image Copy
    def __copy__(self):
        new_image = self.__class__(self.height, self.width, self.columns_blocks, self.rows_blocks)
        new_image.image = copy(self.image)
        new_image.rotated_image = copy(self.rotated_image)
        return new_image

    def __deepcopy__(self, memo=None):
        if memo is None:
            memo = {}
        new_image = self.__class__(self.height, self.width, self.columns_blocks, self.rows_blocks)
        memo[id(self)] = new_image
        new_image.image = deepcopy(self.image, memo)
        new_image.rotated_image = deepcopy(self.rotated_image, memo)
        return new_image
    #endregion