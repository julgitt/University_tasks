from random import shuffle
from typing import Tuple, Optional
from reversi import ReversiState


class AlphaBetaSearch:

    def __init__(self, alpha: int = -1000, beta: int = 1000):
        self.alpha = alpha
        self.beta = beta

    @staticmethod
    def heuristic(state: ReversiState):
        res = 0
        for y in range(state.size):
            for x in range(state.size):
                b = state.board[y][x]
                if b == 0:
                    res -= state.WEIGHTS[y][x]
                elif b == 1:
                    res += state.WEIGHTS[y][x]
        return res

    def max_value(self, state: ReversiState, depth: int, player: int, alpha: int, beta: int) \
            -> Tuple[int, Optional[Tuple[int, int]]]:
        best_move = None
        if depth == 0:
            return self.heuristic(state), best_move
        elif state.terminal():
            return state.result(), best_move

        value = - float("inf")
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
            return self.heuristic(state), best_move
        elif state.terminal():
            return state.result(), best_move

        value = float("inf")
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
