from random import shuffle
from typing import Tuple, Optional
from reversi import ReversiState
import sys


class AlphaBetaSearch:

    def __init__(self, alpha: int = -1000, beta: int = 1000):
        self.alpha = alpha
        self.beta = beta

    @staticmethod
    def heuristic(state: ReversiState):
        res = 0
        res2 = 0
        for y in range(state.size):
            for x in range(state.size):
                b = state.board[y][x]
                if b == 0:
                    res -= state.WEIGHTS[y][x]
                    res2 += state.WEIGHTS[y][x]
                elif b == 1:
                    res += state.WEIGHTS[y][x]
                    res2 += state.WEIGHTS[y][x]

        if res2 == 0:
            res2 = 1
        return res

    @staticmethod
    def corners_heuristic(state: ReversiState):
        max_corners = min_corners = 0
        for y, x in state.CORNERS:
            b = state.board[y][x]
            if b == 1:
                max_corners += 1
            if b == 0:
                min_corners += 1
        bonus = 0
        d = max_corners - min_corners
        if max_corners + min_corners != 0:
            bonus = 100 * (max_corners - min_corners)/(max_corners + min_corners)
        return d


    def close_corner_penalty(self, state):
        min_close = max_close = 0
        for y, x in state.CLOSE_CORNERS:
            b = state.board[y][x]
            if b is None:
                for _y, _x in state.CLOSE_CORNERS[(y, x)]:
                    _b = state.board[_y][_x]
                    if _b == 1:
                        max_close += 1.0
                    if _b == 0:
                        min_close += 1.0
        penalty = 0
        d = max_close - min_close
        if (max_close + min_close != 0):
            penalty = 100.0 * (max_close - min_close)/(max_close + min_close)
        return -d

    @staticmethod
    def another_heuristic(state: ReversiState):
        return state.result()
        #return 100 * state.result() / ((state.size * state.size) - len(state.free_fields))

    def max_value(self, state: ReversiState, depth: int, player: int, alpha: int, beta: int) \
            -> Tuple[int, Optional[Tuple[int, int]]]:
        best_move = None
        if depth == 0:
            return int(
                1.2 * self.heuristic(state) + self.another_heuristic(state)
                + 3.5 * self.corners_heuristic(state) + 2 * self.close_corner_penalty(state)
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
                1.2 * self.heuristic(state) + self.another_heuristic(state)
                + 1.2 * self.corners_heuristic(state) + 2.5 * self.close_corner_penalty(state)
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
