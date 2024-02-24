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
    def all_moves(self, other_piece_pos = None):
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
        moves = self._filter_blocked_moves(moves, other_piece_pos)
        return list(filter(self._is_within_board_bounds, moves))
    
    def _filter_blocked_moves(self, moves, other_piece_pos) -> List[Tuple[str, int]]:
        if other_piece_pos is not None:
            moves = [move for move in moves if move != other_piece_pos]
        return moves
        
    def __eq__(self, other):
        return (isinstance(other, King) and
                self.col == other.col and
                self.row == other.row)


class Rook(Piece):
    def all_moves(self, king_pos : Tuple[str, int]):
        all_moves = [col + str(self.row) for col in "abcdefgh" if col != self.col] \
                  + [self.col + str(row) for row in range(1, 9) if row != self.row]
        valid_moves =  [move for move in all_moves if self._is_path_clear(move, king_pos)]
        return list(filter(self._is_within_board_bounds, valid_moves))
    
    def _is_path_clear(self, move : Tuple[str, int], king_pos : Tuple[str, int] ) -> bool:
        target_col, target_row = move
        king_col, king_row = king_pos

        if target_col == self.col == king_col:  # Ruch w pionie
            min_row = min(int(target_row), int(self.row))
            max_row = max(int(target_row), int(self.row))
            if min_row <= int(king_row) <= max_row:
                return False
        elif target_row == self.row == king_row:  # Ruch w poziomie
            min_col = min(target_col, self.col)
            max_col = max(target_col, self.col)
            if min_col <= king_col <= max_col:
                return False
        return True

    def __eq__(self, other):
        return (isinstance(other, Rook) and
                self.col == other.col and
                self.row == other.row)