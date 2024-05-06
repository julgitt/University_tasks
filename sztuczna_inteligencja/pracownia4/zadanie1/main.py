from random import choice
from typing import List, Tuple, Optional
from turtle import *
import sys


MAX = 100
MIN = -100

class Printer:
    def __init__(self, size: int = 8):
        self.length = 50
        self.sx = -100
        self.sy = 0
        self.size = size

    def print_square(self, x: int, y: int, col: str) -> None:
        tracer(0, 1)
        fillcolor(col)
        pu()
        goto(self.sx + x * self.length, self.sy + y * self.length)
        pd()
        begin_fill()
        for _ in range(4):
            fd(self.length)
            rt(90)
        end_fill()
        update()

    def print_circle(self, x: int, y: int, col: str) -> None:
        tracer(0, 1)
        fillcolor(col)
        pu()
        goto(self.sx + x * self.length + self.length / 2, self.sy + y * self.length - self.length)
        pd()
        begin_fill()
        circle(self.length / 2)
        end_fill()
        update()


class Board:
    # y x
    DIRS: List[Tuple[int, int]] = [(0, 1), (1, 0), (-1, 0), (0, -1),
                                   (1, 1), (-1, -1), (1, -1), (-1, 1)]

    def __init__(self, size: int = 8):
        self.printer: Printer = Printer()
        self.size: int = size
        self.board: List[List[Optional[int]]] = self.initial_board()
        self.free_fields = set()
        self.move_list = []
        self.history = []
        for i in range(self.size):
            for j in range(self.size):
                if self.board[i][j] is None:
                    self.free_fields.add((j, i))

    def initial_board(self) -> List[List[Optional[int]]]:
        board = [[None] * self.size for _ in range(self.size)]
        board[3][3] = 1
        board[4][4] = 1
        board[3][4] = 0
        board[4][3] = 0
        return board

    def draw(self):
        for i in range(self.size):
            res = []
            for j in range(self.size):
                board = self.board[i][j]
                if board is None:
                    res.append('.')
                elif board == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res))
        print('')

    def show(self):
        for i in range(self.size):
            for j in range(self.size):
                self.printer.print_square(j, i, 'green')

        for i in range(self.size):
            for j in range(self.size):
                if self.board[i][j] == 1:
                    self.printer.print_circle(j, i, 'black')
                if self.board[i][j] == 0:
                    self.printer.print_circle(j, i, 'white')

    def moves(self, player: int) -> List[Optional[Tuple[int, int]]]:
        res = []
        for (x, y) in self.free_fields:
            if any(self.can_beat(x, y, direction, player)
                   for direction in self.DIRS):
                res.append((x, y))
        if not res:
            return [None]
        return res

    def can_beat(self, x: int, y: int, direction: Tuple[int, int], player: int) -> bool:
        dx, dy = direction
        x += dx
        y += dy
        opponent_block_length = 0
        opponent = 1 - player
        while self.get(x, y) == opponent:
            x += dx
            y += dy
            opponent_block_length += 1
        return opponent_block_length > 0 and self.get(x, y) == player

    def get(self, x: int, y: int) -> Optional[List[List[Optional[int]]]]:
        if 0 <= x < self.size and 0 <= y < self.size:
            return self.board[y][x]
        return None

    def do_move(self, move: Optional[Tuple[int, int]], player: int) -> None:
        self.history.append([x.copy() for x in self.board])
        self.move_list.append(move)

        if move is None:
            return
        x, y = move
        x0, y0 = move
        self.board[y][x] = player
        self.free_fields -= {move}
        for dx, dy in self.DIRS:
            x, y = x0, y0
            to_beat = []
            x += dx
            y += dy
            opponent = 1 - player
            while self.get(x, y) == opponent:
                to_beat.append((x, y))
                x += dx
                y += dy
            if self.get(x, y) == player:
                for (nx, ny) in to_beat:
                    self.board[ny][nx] = player

    def revert_move(self):
        self.board = self.history.pop()
        last_move = self.move_list.pop()
        self.free_fields |= {last_move}

    def result(self) -> int:
        res = 0
        for y in range(self.size):
            for x in range(self.size):
                board = self.board[y][x]
                if board == 0:
                    res -= 1
                elif board == 1:
                    res += 1
        return res

    def terminal(self) -> bool:
        if not self.free_fields:
            return True
        if len(self.move_list) < 2:
            return False
        is_move_impossible = self.move_list[-1] == self.move_list[-2] is None
        return is_move_impossible

    def random_move(self, player: int):
        ms = self.moves(player)
        if ms:
            return choice(ms)
        return [None]


class AlphaBetaSearch:
    def __init__(self, alpha: int, beta: int, depth: int = 1000):
        self.alpha = alpha
        self.beta = beta
        self.depth = depth

    def best_move(self, state: Board, player: int):
        return self.min_value(state, self.depth, player, self.alpha, self.beta)

    def max_value(self, state: Board, depth: int, player: int, alpha: int, beta: int) \
            -> Tuple[int, Optional[Tuple[int, int]]]:
        best_move = None
        if state.terminal or depth == 0:
            return state.result(), best_move
        value = - float("inf")
        for move in state.moves(player):
            state.do_move(move, player)
            value = max(value, self.min_value(state, depth - 1, 1 - player, alpha, beta)[0])
            if value >= beta:
                best_move = move
                if move is not None:
                    state.revert_move()
                return value, best_move
            if value > alpha:
                alpha = value
                best_move = move
            if move is not None:
                state.revert_move()
        return value, best_move

    def min_value(self, state: Board, depth, player: int, alpha, beta) -> Tuple[int, Optional[Tuple[int, int]]]:
        best_move = None
        if state.terminal() or depth == 0:
            return state.result(), best_move
        value = float("inf")

        for move in state.moves(player):
            state.do_move(move, player)
            value = min(value, self.max_value(state, depth - 1, 1 - player, alpha, beta)[0])
            if value <= alpha:
                best_move = move
                if move is not None:
                    state.revert_move()
                return value, best_move
            if value < beta:
                beta = value
                best_move = move
            if move is not None:
                state.revert_move()
        return value, best_move


class Program:
    if __name__ == "__main__":
        win = 0
        loss = 0
        draw = 0
        for i in range(1000):
            player = 0
            board = Board()
            search = AlphaBetaSearch(MIN, MAX)

            while True:
                #board.draw()
                #board.show()
                #print(player)
                if player == 1:
                    m = board.random_move(player)
                    board.do_move(m, player)
                else:
                    _, m = search.best_move(board, player)
                    board.do_move(m, player)

                player = 1 - player
                #input()
                if board.terminal():
                    break

            board.draw()
            #board.show()
            print(f'Result: {board.result()}')
            if board.result() > 0:
                loss += 1
            elif board.result() < 0:
                win += 1
            else:
                draw += 1
        print(f'{loss}:{win}:{draw}')
        #input()
        sys.exit(0)
