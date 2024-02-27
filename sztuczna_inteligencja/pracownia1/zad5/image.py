import copy
import random
from typing import List

class Image:
    
    def __init__(self, height: int, width: int, columns_blocks: List[int], rows_blocks: List[int]):
        self.height = height
        self.width = width
        self.columns_blocks = columns_blocks
        self.rows_blocks = rows_blocks
        self.image = []
        self.rotated_image = []
    
    #region getters    
    def get_row(self, index: int) -> List[str]:
        return self.image[index]

    def get_column(self, index: int) -> List[str]:
        return self.rotated_image[index]
    #endregion
    
    #region setters
    def set_row(self, index: int, new_row: str):
        self.image[index] = new_row
        self.update_rotated_image()
    
    def set_column(self, index, new_column):
        self.rotated_image[index] = new_column  
        self.update_image()
    #endregion
    
    #region updating_image    
    def swap_cell(self, row_id, col_id):
        row = self.image[row_id]
        current_char = row[col_id]
        new_char = '#' if current_char == '.' else '.'
        self.image[row_id] = row[:col_id] + new_char + row[col_id + 1:]
        self.update_rotated_image()
        
    def regenerate(self):
        self.image = []
        for _ in range(self.height):
            self.image.append(''.join(random.choice('.#') for _ in range(self.width)))
        self.update_rotated_image()
            
    def update_rotated_image(self):
        self.rotated_image = []
        for i in range(self.width):
            self.rotated_image.append("".join([line[i] for line in self.image]))
    
    def update_image(self):
        self.image = []
        for i in range(self.width):
            self.image.append("".join([line[i] for line in self.rotated_image]))
    #endregion
    
    #region incorrect_lines_getters     
    def get_random_incorrect_row_id(self):
        incorrect_rows = [i for i in range(self.height) if self.opt_dist(self.get_row(i), self.rows_blocks[i]) > 0]
        return random.choice(incorrect_rows) if incorrect_rows else -1

    def get_random_incorrect_column_id(self):
        incorrect_columns = [i for i in range(self.width) if self.opt_dist(self.get_column(i), self.columns_blocks[i]) > 0]
        return random.choice(incorrect_columns) if incorrect_columns else -1
    #endregion
    
    #region algorithm_functions
    def opt_dist(self, line, block_size):
        min_operations = float('inf')
        
        for i in range(len(line) - block_size + 1):
            operations = line.count('#', 0, i) + line.count('.', i, i + block_size) + line.count('#', block_size + i, len(line))
            if min_operations > operations: 
                min_operations = operations
                
        return min_operations
    

    def find_best_cell_in_row(self, i):
        best_opers = 100   # how many operations to correct 
        best_cell = 0    # column index of the best_cell
        
        for k in range(0, self.width):
            img_copy = copy.deepcopy(self)
            img_copy.swap_cell(i, k)
            current_opers = img_copy.opt_dist(img_copy.get_row(i), img_copy.rows_blocks[i])
            for j in range(img_copy.width):
                current_opers += img_copy.opt_dist(img_copy.get_column(j), img_copy.columns_blocks[j])
            if current_opers < best_opers:
                best_opers = current_opers
                best_cell = k
                
        return best_cell, best_opers
    
    def find_best_cell_in_column(self, i):
        best_opers = 100  # how many operations to correct 
        best_cell = 0    # column index of the best_cell
        
        for k in range(0, self.height):
            img_copy = copy.deepcopy(self)
            img_copy.swap_cell(k, i)
            current_opers = img_copy.opt_dist(img_copy.get_column(i), img_copy.columns_blocks[i])
            for j in range(img_copy.height):
                current_opers += img_copy.opt_dist(img_copy.get_row(j), img_copy.rows_blocks[j])
            if current_opers < best_opers:
                best_opers = current_opers
                best_cell = k
                
        return best_cell, best_opers
    #endregion
    
    #region object_copy
    def __copy__(self):
        new_image = self.__class__(self.height, self.width, self.columns_blocks, self.rows_blocks)
        new_image.image = copy.copy(self.image)
        new_image.rotated_image = copy.copy(self.rotated_image)
        return new_image

    # Implementacja metody __deepcopy__ dla glebokiej kopii
    def __deepcopy__(self, memo=None):
        if memo is None:
            memo = {}
        new_image = self.__class__(self.height, self.width, self.columns_blocks, self.rows_blocks)
        memo[id(self)] = new_image
        new_image.image = copy.deepcopy(self.image, memo)
        new_image.rotated_image = copy.deepcopy(self.rotated_image, memo)
        return new_image
    #endregion