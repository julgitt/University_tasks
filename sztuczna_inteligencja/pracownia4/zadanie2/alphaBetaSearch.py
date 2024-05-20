from random import shuffle
from typing import Tuple, Optional
from reversi import ReversiState
import sys


class AlphaBetaSearch:

    def __init__(self, alpha: int = -1000, beta: int = 1000):
        self.alpha = alpha
        self.beta = beta

    def max_value(self, state: ReversiState, depth: int, player: int, alpha: int, beta: int) \
            -> Tuple[int, Optional[Tuple[int, int]]]:
        best_move = None
        if depth == 0:
            return state.heuristic(), best_move
        elif state.terminal():
            return state.result() * 1000, best_move

        value = - sys.maxsize
        moves = state.moves(player)
        shuffle(moves)
        for move in moves:
            state.do_move(move, player)
            value = max(value, self.min_value(state, depth - 1, 1 - player, alpha, beta)[0])
            state.undo_move()
            if value >= beta:
                best_move = move
                return value, best_move
            if value > alpha:
                alpha = value
                best_move = move
        return value, best_move

    def min_value(self, state: ReversiState, depth, player: int, alpha, beta) -> Tuple[int, Optional[Tuple[int, int]]]:
        best_move = None
        if depth == 0:
            return state.heuristic(), best_move
        elif state.terminal():
            return state.result(), best_move

        value = sys.maxsize
        moves = state.moves(player)
        shuffle(moves)
        for move in moves:
            state.do_move(move, player)
            value = min(value, self.max_value(state, depth - 1, 1 - player, alpha, beta)[0])
            state.undo_move()
            if value <= alpha:
                best_move = move
                return value, best_move
            if value < beta:
                beta = value
                best_move = move
        return value, best_move
