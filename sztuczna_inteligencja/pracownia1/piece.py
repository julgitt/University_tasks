from abc import ABC, abstractmethod
from letters import Letter
from typing import List, Tuple

class Piece(ABC):
    def __init__(self, pos : Tuple[str, int]):
        self.position = pos
        self.col = pos[0]
        self.row = int(pos[1])
        
    @abstractmethod
    def all_moves(self, other_piece) -> List[Tuple[str, int]]:
        pass
    
    def _is_within_board_bounds(self, move : Tuple[str, int]) -> bool:
        col, row = move
        return "a" <= col <= "h" and 1 <= int(row) <= 8
    
    def __eq__(self, other):
        pass

    def __hash__(self):
        return hash((self.row, self.col))


class King(Piece):
    def all_moves(self, obstructed_cell_pos: Tuple[str, int] = None):
        dec_col = Letter.decrement_letter(self.col)
        dec_row = int(self.row) - 1
        inc_col = Letter.increment_letter(self.col)
        inc_row = int(self.row) + 1
        moves = [
            self.col + str(dec_row), # n
            inc_col + str(dec_row),  # ne
            inc_col + str(self.row), # e
            inc_col + str(inc_row),  # ew
            self.col + str(inc_row), # w
            dec_col + str(inc_row),  # ws
            dec_col + str(self.row), # s
            dec_col + str(dec_row)   # sn
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