from abc import ABC, abstractmethod
from typing import List

from letters import Letter

class Piece(ABC):
    def __init__(self, pos: str):
        self.position = pos
        self.col = pos[0]
        self.row = pos[1]
        
    @abstractmethod
    def all_moves(self, obstructed_cell_pos: str = None) -> List[str]:
        pass
    
    def _is_within_board_bounds(self, move: str) -> bool:
        col, row = move
        return "a" <= col <= "h" and '1' <= row <= '8'


class King(Piece):
    def all_moves(self, obstructed_cell_pos: str = None):
        prev_col = Letter.previous_letter(self.col)
        prev_row = str(int(self.row) - 1)
        next_col = Letter.next_letter(self.col)
        next_row = str(int(self.row) + 1)
        moves = [
            self.col + prev_row, # n
            next_col + prev_row, # ne
            next_col + self.row, # e
            next_col + next_row, # ew
            self.col + next_row, # w
            prev_col + next_row, # ws
            prev_col + self.row, # s
            prev_col + prev_row # sn
        ]
        filtered_moves = self._filter_blocked_moves(moves, obstructed_cell_pos)
        
        valid_moves = []
        for move in filtered_moves:
            if self._is_within_board_bounds(move):
                valid_moves.append(move)
        
        return valid_moves
    
    def _filter_blocked_moves(self, moves, obstructed_cell_pos: str = None) -> List[str]:
        if obstructed_cell_pos is not None:
            filtered_moves = []
            for move in moves:
                if move != obstructed_cell_pos:
                    filtered_moves.append(move)
            return filtered_moves
        
        return moves


class Rook(Piece):
    def all_moves(self, obstructed_cell_pos: str = None):
        all_moves = [col + self.row for col in "abcdefgh" if col != self.col] \
                  + [self.col + row for row in "12345678" if row != self.row]
        
        valid_moves = []
        
        for move in all_moves:
            if self._is_path_clear(move, obstructed_cell_pos) and self._is_within_board_bounds(move):
                valid_moves.append(move)
        
        return valid_moves
    
    def _is_path_clear(self, move: str, obstructed_cell_pos: str) -> bool:
        target_col, target_row = move
        cell_col, cell_row = obstructed_cell_pos

        if target_col == self.col == cell_col:  # Ruch w pionie
            min_row = min(target_row, self.row)
            max_row = max(target_row, self.row)
            if min_row <= cell_row <= max_row:
                return False
        elif target_row == self.row == cell_row:  # Ruch w poziomie
            min_col = min(target_col, self.col)
            max_col = max(target_col, self.col)
            if min_col <= cell_col <= max_col:
                return False
        
        return True