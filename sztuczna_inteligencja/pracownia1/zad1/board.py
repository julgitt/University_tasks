from piece import Rook, King, Piece

class Board:
    def __init__(self, player_color: str, white_king: King,
                 white_rook: Rook, black_king: King):
        self.player_turn = player_color
        self.white_king = white_king
        self.white_rook = white_rook
        self.black_king = black_king
        
    def swap_turn(self):
        self.player_turn = "black" if self.player_turn == "white" else "white"
    
    def is_checkmate(self) -> bool:
        if self.player_turn == "white":
            if self.if_rook_captures(self.white_rook, self.black_king) \
               or self.if_king_captures(self.white_king, self.black_king):
                return True
        else:
            if self.if_king_captures(self.black_king, self.white_king) \
               or self.if_king_captures(self.black_king, self.white_rook):
                return True
        return False
               
    def if_rook_captures(self, rook: Rook, piece: Piece) -> bool:
        return rook.col == piece.col or rook.row == piece.row
    
    def if_king_captures(self, king: King, piece: Piece) -> bool:
        for move in king.all_moves():
            if move[0] == piece.col and move[1] == piece.row:
                return True
        return False
        
    def __str__(self):
        return f"turn:{self.player_turn}, BK:{self.black_king.position}, " + \
                f"WK:{self.white_king.position}, WR:{self.white_rook.position}\n"
    
    def __eq__(self, other):
        return (isinstance(other, Board) and
                self.player_turn == other.player_turn and
                self.white_king == other.white_king and
                self.white_rook == other.white_rook and
                self.black_king == other.black_king)

    def __hash__(self):
        return hash((self.player_turn, self.white_king.position,
                     self.white_rook.position, self.black_king.position))