from abc import ABC, abstractmethod
from typing import List, Tuple

from letters import Letter

class Piece(ABC):
    def __init__(self, pos: Tuple[str, int]):
        self.position = pos
        self.col = pos[0]
        self.row = int(pos[1])
        
    @abstractmethod
    def all_moves(self, obstructed_cell_pos: Tuple[str, int] = None) -> List[Tuple[str, int]]:
        pass
    
    def _is_within_board_bounds(self, move: Tuple[str, int]) -> bool:
        col, row = move
        return "a" <= col <= "h" and 1 <= int(row) <= 8
    
    def __eq__(self, other):
        pass

    def __hash__(self):
        return hash((self.row, self.col))


class King(Piece):
    def all_moves(self, obstructed_cell_pos: Tuple[str, int] = None):
        prev_col = Letter.previous_letter(self.col)
        prev_row = int(self.row) - 1
        next_col = Letter.next_letter(self.col)
        next_row = int(self.row) + 1
        moves = [
            self.col + str(prev_row), # n
            next_col + str(prev_row), # ne
            next_col + str(self.row), # e
            next_col + str(next_row), # ew
            self.col + str(next_row), # w
            prev_col + str(next_row), # ws
            prev_col + str(self.row), # s
            prev_col + str(prev_row)  # sn
        ]
        moves = self._filter_blocked_moves(moves, obstructed_cell_pos)
        
        return list(filter(self._is_within_board_bounds, moves))
    
    def _filter_blocked_moves(self, moves, obstructed_cell_pos: Tuple[str, int] = None) -> List[Tuple[str, int]]:
        if obstructed_cell_pos is not None:
            moves = [move for move in moves if move != obstructed_cell_pos]
        
        return moves
        
    def __eq__(self, other):
        return (isinstance(other, King) and
                self.col == other.col and
                self.row == other.row)


class Rook(Piece):
    def all_moves(self, obstructed_cell_pos: Tuple[str, int] = None):
        all_moves = [col + str(self.row) for col in "abcdefgh" if col != self.col] \
                  + [self.col + str(row) for row in range(1, 9) if row != self.row]
        valid_moves =  [move for move in all_moves if self._is_path_clear(move, obstructed_cell_pos)]
        
        return list(filter(self._is_within_board_bounds, valid_moves))
    
    def _is_path_clear(self, move: Tuple[str, int], obstructed_cell_pos: Tuple[str, int]) -> bool:
        target_col, target_row = move
        cell_col, cell_row = obstructed_cell_pos

        if target_col == self.col == cell_col:  # Ruch w pionie
            min_row = min(int(target_row), int(self.row))
            max_row = max(int(target_row), int(self.row))
            if min_row <= int(cell_row) <= max_row:
                return False
        elif target_row == self.row == cell_row:  # Ruch w poziomie
            min_col = min(target_col, self.col)
            max_col = max(target_col, self.col)
            if min_col <= cell_col <= max_col:
                return False
        
        return True

    def __eq__(self, other):
        return (isinstance(other, Rook) and
                self.col == other.col and
                self.row == other.row)