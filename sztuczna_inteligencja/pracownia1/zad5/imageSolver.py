from typing import List, Tuple

from image import Image


class ImageSolver:

    def __init__(self, height: int, width: int, 
                columns_blocks: List[int], rows_blocks: List[int]):
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
                    self._handle_row(random_row_id)
                elif random_column_id != -1:
                    self._handle_column(random_column_id)
                else:
                    return self.image.image   
            
    def _handle_row(self, id: int) -> None:
        column_id, operations = self.image.find_best_cell_in_row(id)
        if operations >= 17:
            row_to_change = self.image.get_row(id)
            self.image.set_row(id, self._change_line(row_to_change, self.rows_blocks[id]))
        else:     
            self.image.swap_cell(id, column_id)
        
    def _handle_column(self, id: int) -> None:
        row_id, operations = self.image.find_best_cell_in_column(id)
        if operations >= 17:
            column_to_change = self.image.get_column(id)
            self.image.set_column(id, self._change_line(column_to_change, self.columns_blocks[id]))
        else: 
            self.image.swap_cell(row_id, id)
        
    @staticmethod
    def _change_line(line: str, block_size: str) -> str:
        min_operations = float('inf')
        fixed_line = line

        for i in range(len(line) - block_size + 1):
            operations = line.count('#', 0, i) + line.count('.', i, i + block_size) + line.count('#', block_size + i, len(line))
            if min_operations > operations: 
                min_operations = operations
                fixed_line = '.' * i + '#' * block_size + '.' * (len(line) - block_size - i)
        
        return fixed_line