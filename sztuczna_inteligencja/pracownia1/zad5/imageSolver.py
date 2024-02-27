from typing import List, Tuple

from image import Image

class ImageSolver:

    def __init__(self, height, width, columns_blocks, rows_blocks):
        self.columns_blocks = columns_blocks
        self.rows_blocks = rows_blocks
        self.image = Image(height, width, columns_blocks, rows_blocks)
        
    
    def solve(self, max_iterations: int) -> List[str]:
        while True:
            self.image.regenerate()
            for _ in range(max_iterations):
                random_row_id = self.image.get_random_incorrect_row_id()
                random_column_id = self.image.get_random_incorrect_column_id()
                if random_row_id != -1:
                    handle_row(self.image, random_row_id)
                elif random_column_id != -1:
                    handle_column(self.image, random_column_id)
                else:
                    return self.image.image
           
           
def handle_row(self, id: int) -> None:
    column_id, operations = self.image.find_best_cell_in_row(id)
    if operations >= 17:
        self.image.set_row(id, fix_line(self.image.get_row(id), self.rows_blocks[id]))
    else:     
        self.image.swap_cell(id, column_id)
    
    
def handle_column(self, id: int) -> None:
    row_id, operations = self.image.find_best_cell_in_column(id)
    if operations >= 17:
        self.image.set_column(id, fix_line(self.image.get_column(id), self.columns_blocks[id]))
    else: 
        self.image.swap_cell(row_id, id)
    
    
def fix_line(line: str, D: str) -> str:
    min_operations = float('inf')
    fixed_line = line
    
    for i in range(len(line) - D + 1):
        operations = line.count('#', 0, i) + line.count('.', i, i + D) + line.count('#', D + i, len(line))
        if min_operations > operations: 
            min_operations = operations
            fixed_line = '.' * i + '#' * D + '.' * (len(line) - D - i)
    
    return fixed_line