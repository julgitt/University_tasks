import queue
from piece import Rook,King
from board import Board
from typing import List

class SolveEndgame:
    def __init__(self):
        self.visited = set()
        self.queue = queue.Queue()
             
    def solve(self, board : Board) -> float:
        self.queue.put((board, 0, [str(board)]))
         
        while not self.queue.empty():
            board, move_count, prev_boards = self.queue.get()
            
            if board.player_turn == "black":
                pat = self._solve_black_turn(board, move_count, prev_boards)
                if (pat == True and board.swap_turn().is_checkmate()):
                    return [str(move_count), ''.join(prev_boards)]
            elif board.is_checkmate():
                    return [str(move_count), ''.join(prev_boards)]
            else:  
                self._solve_white_turn(board, move_count, prev_boards)
                            
        return "inf" 
    
    def _solve_black_turn(self, board : Board, move_count : int, 
                          prev_boards : List[Board]) -> bool:
        checkmate_flag = True
        for new_pos in board.black_king.all_moves():
            new_board = Board("white", board.white_king, board.white_rook, King(new_pos))
            if self._is_valid_board(new_board):
                checkmate_flag = False
                if self._is_not_visited(new_board):
                    self._add_new_board_to_queue(new_board, prev_boards, move_count)
            
        return checkmate_flag
    
    def _solve_white_turn(self, board : Board, move_count : int,
                          prev_boards : List[Board]) -> None:
        if not board._if_king_checks(board.black_king,board.white_rook):
            for new_pos in board.white_king.all_moves(board.white_rook.position):
                new_board = Board("black", King(new_pos), board.white_rook, board.black_king)    
                if self._is_not_visited(new_board) and self._is_valid_board(new_board):
                    self._add_new_board_to_queue(new_board, prev_boards, move_count)
        if board._if_king_checks(board.black_king,board.white_king):
            return                  
        for new_pos in board.white_rook.all_moves(board.white_king.position):
            new_board = Board("black", board.white_king, Rook(new_pos), board.black_king)
            if self._is_not_visited(new_board) and self._is_valid_board(new_board):
                self._add_new_board_to_queue(new_board, prev_boards, move_count)
    
    def _is_valid_board (self, new_board : Board) -> bool:
        return not new_board.is_checkmate()
            
    def _is_not_visited (self, new_board : Board):
        return hash(new_board) not in self.visited   
    
    def _add_new_board_to_queue(self, new_board : Board, prev_boards : List[Board], move_count: int) -> None:
        prev_boards_copy = prev_boards.copy()
        prev_boards_copy.append(str(new_board))
        self.queue.put((new_board, move_count + 1, prev_boards_copy))
        self.visited.add(hash(new_board))