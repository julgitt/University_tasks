from piece import Rook, King, Piece

class Board:
    def __init__(self, player_color : str, white_king : King, white_rook : Rook, black_king : King):
        self.player_turn = player_color
        self.white_king = white_king
        self.white_rook = white_rook
        self.black_king = black_king
        
    def swap_turn(self):
        if self.player_turn == "white":
            self.player_turn = "black"
        else: self.player_turn = "white"
        return self
    
    def is_checkmate(self) -> bool:
        if self.player_turn == "white":
            if self._if_rook_checks(self.white_rook, self.black_king) or self._if_king_checks(self.white_king, self.black_king):
                return True
        else:
            if self._if_king_checks(self.black_king, self.white_king) or self._if_king_checks(self.black_king, self.white_rook):
                return True
        return False
               
    def _if_rook_checks(self, rook : Rook, piece : Piece) -> bool:
        return rook.col == piece.col or rook.row == piece.row
    
    def _if_king_checks(self, king : King, piece : Piece) -> bool:
        for [col, row] in king.all_moves():
            if [col, int(row)] == [piece.col, piece.row]:
                return True
        return False
        
    def __str__(self):
        return f"tura={self.player_turn}, czarny krol={self.black_king.position}," + \
                f"white_king={self.white_king.position}, white_rook={self.white_rook.position}\n"
    
    def __eq__(self, other):
        return (isinstance(other, Board) and
                self.player_color == other.player_color and
                self.white_king == other.white_king and
                self.white_rook == other.white_rook and
                self.black_king == other.black_king)

    def __hash__(self):
        return hash((self.player_turn, self.white_king.position,
                     self.white_rook.position, self.black_king.position))