from random import shuffle
from typing import Tuple, Optional
from reversi import ReversiState
import sys


class AlphaBetaSearch:

    def __init__(self, alpha: int = -1000, beta: int = 1000):
        self.alpha = alpha
        self.beta = beta

    @staticmethod
    def discs_score_heuristic(state: ReversiState):
        return state.result()

    @staticmethod
    def weight_heuristic(state: ReversiState) -> int:
        res = 0
        for y in range(state.size):
            for x in range(state.size):
                b = state.board[y][x]
                if b == 0:
                    res -= state.WEIGHTS[y][x]
                elif b == 1:
                    res += state.WEIGHTS[y][x]

        return res

    @staticmethod
    def corners_heuristic(state: ReversiState) -> int:
        res = 0
        for y, x in state.CORNERS:
            b = state.board[y][x]
            if b == 1:
                res += 1
            if b == 0:
                res -= 1
        return res

    @staticmethod
    def close_corner_heuristic(state: ReversiState) -> int:
        res = 0
        for y, x in state.CLOSE_CORNERS:
            b = state.board[y][x]
            if b is None:
                for _y, _x in state.CLOSE_CORNERS[(y, x)]:
                    _b = state.board[_y][_x]
                    if _b == 1:
                        res += 1.0
                    if _b == 0:
                        res -= 1.0
        return - res

    @staticmethod
    def mobility_heuristic(state: ReversiState) -> int:
        if state.moves(0) is None:
            moves_min = 0
        else:
            moves_min = len(state.moves(0))
        if state.moves(1) is None:
            moves_max = 0
        else:
            moves_max = len(state.moves(1))
        return moves_max - moves_min

    def max_value(self, state: ReversiState, depth: int, player: int, alpha: int, beta: int) \
            -> Tuple[int, Optional[Tuple[int, int]]]:
        best_move = None
        if depth == 0:
            return int(
                1.5 * self.discs_score_heuristic(state) + 1.2 * self.weight_heuristic(state)
                + 6 * self.corners_heuristic(state) + 5 * self.close_corner_heuristic(state)
                + 5 * self.mobility_heuristic(state)
            ), best_move
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
            return int(
                2 * self.discs_score_heuristic(state) + self.weight_heuristic(state)
                + 6 * self.corners_heuristic(state) + 5 * self.close_corner_heuristic(state)
                + 5 * self.mobility_heuristic(state)
            ), best_move
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
