from random import choice
from typing import List, Tuple, Optional
from printer import Printer


class ReversiState:
    CORNERS = [(0, 0), (0, 7), (7, 0), (7, 7)]
    DIRS: List[Tuple[int, int]] = [
        (0, 1), (1, 0), (-1, 0), (0, -1),
        (1, 1), (-1, -1), (1, -1), (-1, 1)
    ]

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
    # endregion

    # region Debug
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

    # endregion

    # region Get Possible Moves
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

    # endregion

    # region Do/Undo Move
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

    def undo_move(self) -> None:
        self.board = self.history.pop()
        last_move = self.move_list.pop()
        if last_move is not None:
            self.free_fields |= {last_move}

    # endregion

    # region Board State
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

    # endregion

    # region Heuristics
    WEIGHTS = [
        [50, -20, 11, 8, 8, 11, -20, 50],
        [-20, -50, -4, 1, 1, -4, -50, -20],
        [11, -4, 2, 2, 2, 2, -4, 11],
        [8, 1, 2, -3, -3, 2, 1, 8],
        [8, 1, 2, -3, -3, 2, 1, 8],
        [11, -4, 2, 2, 2, 2, -4, 11],
        [-20, -50, -4, 1, 1, -4, -50, -20],
        [50, -20, 11, 8, 8, 11, -20, 50]
    ]

    def score_heuristic(self):
        return self.result()

    def weight_heuristic(self) -> int:
        res = 0
        for y in range(self.size):
            for x in range(self.size):
                b = self.board[y][x]
                if b == 0:
                    res -= self.WEIGHTS[y][x]
                elif b == 1:
                    res += self.WEIGHTS[y][x]
        return res

    def corners_heuristic(self) -> int:
        res = 0
        for y, x in self.CORNERS:
            b = self.board[y][x]
            if b == 1:
                res += 1
            if b == 0:
                res -= 1
        return res

    def mobility_heuristic(self) -> int:
        if self.moves(0) is None:
            moves_min = 0
        else:
            moves_min = len(self.moves(0))
        if self.moves(1) is None:
            moves_max = 0
        else:
            moves_max = len(self.moves(1))
        return moves_max - moves_min

    def heuristic(self) -> int:
        return int(
            1.5 * self.score_heuristic() + 1.2 * self.weight_heuristic()
            + 6 * self.corners_heuristic() + 5 * self.mobility_heuristic()
        )
    # endregion

    # region Ways of Moving
    def random_move(self, player: int) -> Optional[Tuple[int, int]]:
        ms = self.moves(player)
        if ms:
            return choice(ms)
        return None

    def best_move(self, player: int, search, depth: int) -> Optional[Tuple[int, int]]:
        _, move = search.min_value(self, depth, player, search.alpha, search.beta) if player == 0 else \
            search.max_value(self, depth, player, search.alpha, search.beta)
        return move
# endregion
