import random
import sys
from typing import List, Tuple, Optional
from copy import deepcopy


class Jungle:
    PIECE_VALUES: dict = {
        0: 4,
        1: 1,
        2: 2,
        3: 3,
        4: 5,
        5: 7,
        6: 8,
        7: 10
    }
    # player 0, player 1
    DEN_DISTANCE: List[List[List[int]]] = [
        [
            [8, 9, 10, 11, 10, 9, 8],
            [7, 8, 9, 10, 9, 8, 7],
            [6, 7, 8, 9, 8, 7, 6],
            [5, 6, 7, 8, 7, 6, 5],
            [4, 5, 6, 7, 6, 5, 4],
            [3, 4, 5, 6, 5, 4, 3],
            [2, 3, 4, 5, 4, 3, 2],
            [1, 2, 3, 4, 3, 2, 1],
            [0, 1, 2, 3, 2, 1, 0]
        ],
        [
            [0, 1, 2, 3, 2, 1, 0],
            [1, 2, 3, 4, 3, 2, 1],
            [2, 3, 4, 5, 4, 3, 2],
            [3, 4, 5, 6, 5, 4, 3],
            [4, 5, 6, 7, 6, 5, 4],
            [5, 6, 7, 8, 7, 6, 5],
            [6, 7, 8, 9, 8, 7, 6],
            [7, 8, 9, 10, 9, 8, 7],
            [8, 9, 10, 11, 10, 9, 8]
        ]
    ]

    MAXIMAL_PASSIVE: int = 30
    DENS_DIST: int = 0.1
    MX: int = 7
    MY: int = 9
    traps: dict[Tuple[int, int]] = {(2, 0), (4, 0), (3, 1), (2, 8), (4, 8), (3, 7)}
    ponds: dict[Tuple[int, int]] = {(x, y) for x in [1, 2, 4, 5] for y in [3, 4, 5]}
    dens: List[Tuple[int, int]] = [(3, 8), (3, 0)]
    dirs: List[Tuple[int, int]] = [(0, 1), (1, 0), (-1, 0), (0, -1)]
    rat, cat, dog, wolf, jaguar, tiger, lion, elephant = range(8)

    def __init__(self):
        self.board: List[List[Optional[Tuple[int, int]]]] = self.initial_board()
        self.pieces: dict[int, dict[int, Tuple[int, int]]] = {0: {}, 1: {}}

        for y in range(Jungle.MY):
            for x in range(Jungle.MX):
                player_piece = self.board[y][x]
                if player_piece:
                    player, piece = player_piece
                    self.pieces[player][piece] = (x, y)
        self.cur_player = 0
        self.peace_counter = 0
        self.winner = None

    @staticmethod
    def initial_board() -> List[List[Optional[Tuple[int, int]]]]:
        _board = """
        L.....T
        .D...C.
        R.J.W.E
        .......
        .......
        .......
        e.w.j.r
        .c...d.
        t.....l
        """

        board = [x.strip() for x in _board.split() if len(x) > 0]
        piece_to_number = dict(zip('rcdwjtle', range(8)))

        res = []
        for y in range(9):
            raw = 7 * [None]
            for x in range(7):
                piece = board[y][x]
                if piece != '.':
                    if 'A' <= piece <= 'Z':
                        player = 1
                    else:
                        player = 0
                    raw[x] = (player, piece_to_number[piece.lower()])
            res.append(raw)
        return res

    def random_move(self, player: int) -> Optional[Tuple[Tuple[int, int]]]:
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return None

    @staticmethod
    def can_beat(p1: int, p2: int, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> bool:
        if pos1 in Jungle.ponds and pos2 in Jungle.ponds:
            return True  # rat vs rat
        if pos1 in Jungle.ponds:
            return False  # rat in pond cannot beat any piece on land
        if p1 == Jungle.rat and p2 == Jungle.elephant:
            return True
        if p1 == Jungle.elephant and p2 == Jungle.rat:
            return False
        if p1 >= p2:
            return True
        if pos2 in Jungle.traps:
            return True
        return False

    def pieces_comparison(self) -> Optional[int]:
        for i in range(7, -1, -1):
            ps = []
            for player in [0, 1]:
                if i in self.pieces[player]:
                    ps.append(player)
            if len(ps) == 1:
                return ps[0]
        return None

    def rat_is_blocking(self, pos: Tuple[int, int], dx: int, dy: int) -> bool:
        x, y = pos
        nx = x + dx
        for player in [0, 1]:
            if Jungle.rat not in self.pieces[1 - player]:
                continue
            rat_x, rat_y = self.pieces[1 - player][Jungle.rat]
            if (rat_x, rat_y) not in self.ponds:
                continue
            if dy != 0:
                if x == rat_x:
                    return True
            if dx != 0:
                if y == rat_y and abs(x - rat_x) <= 2 and abs(nx - rat_x) <= 2:
                    return True
        return False

    def draw(self) -> None:
        player_pieces = {0: 'rcdwjtle', 1: 'RCDWJTLE'}
        for y in range(Jungle.MY):
            board_str = []
            for x in range(Jungle.MX):
                b = self.board[y][x]
                if b:
                    player, piece = b
                    board_str.append(player_pieces[player][piece])
                else:
                    board_str.append('.')
            print(''.join(board_str))
        print('')

    def moves(self, _player: int) -> List[Tuple[Tuple[int, int], Tuple[int, int]]]:
        res = []
        for piece, pos in self.pieces[_player].items():
            x, y = pos
            for (dx, dy) in Jungle.dirs:
                pos2 = (nx, ny) = (x + dx, y + dy)
                if 0 <= nx < Jungle.MX and 0 <= ny < Jungle.MY:
                    if Jungle.dens[_player] == pos2:
                        continue
                    if pos2 in self.ponds:
                        if piece not in (Jungle.rat, Jungle.tiger, Jungle.lion):
                            continue
                        #  if self.board[ny][nx] is not None:
                        #    continue  # WHY??
                        if piece == Jungle.tiger or piece == Jungle.lion:
                            if dx != 0:
                                dx *= 3
                            if dy != 0:
                                dy *= 4
                            if self.rat_is_blocking(pos, dx, dy):
                                continue
                            pos2 = (nx, ny) = (x + dx, y + dy)
                    if self.board[ny][nx] is not None:
                        pl2, piece2 = self.board[ny][nx]
                        if pl2 == _player:
                            continue
                        if not self.can_beat(piece, piece2, pos, pos2):
                            continue
                    res.append((pos, pos2))
        return res

    def victory(self, player: int) -> bool:
        opponent = 1 - player
        if len(self.pieces[opponent]) == 0:
            self.winner = player
            return True

        x, y = self.dens[opponent]
        if self.board[y][x]:
            self.winner = player
            return True

        if self.peace_counter >= Jungle.MAXIMAL_PASSIVE:
            r = self.pieces_comparison()
            if r is None:
                self.winner = 1  # draw is second player's victory
            else:
                self.winner = r
            return True
        return False

    def do_move(self, move: Optional[Tuple[Tuple[int, int], Tuple[int, int]]]) -> None:
        self.cur_player = 1 - self.cur_player
        if move is None:
            return
        pos1, pos2 = move
        x, y = pos1
        pl, pc = self.board[y][x]

        x2, y2 = pos2
        if self.board[y2][x2]:  # piece taken!
            pl2, pc2 = self.board[y2][x2]
            del self.pieces[pl2][pc2]
            self.peace_counter = 0
        else:
            self.peace_counter += 1

        self.pieces[pl][pc] = (x2, y2)
        self.board[y2][x2] = (pl, pc)
        self.board[y][x] = None

    def result_heuristic(self, player):
        res = 0
        for piece, pos in self.pieces[1 - player].items():
            res -= self.PIECE_VALUES[piece]
        for piece, pos in self.pieces[player].items():
            res += self.PIECE_VALUES[piece]

        return res

    def den_distance_heuristic(self, player):
        res = 0
        for piece, pos in self.pieces[player].items():
            res += self.DEN_DISTANCE[player][pos[1]][pos[0]]

        for piece, pos in self.pieces[1 - player].items():
            res -= self.DEN_DISTANCE[1 - player][pos[1]][pos[0]]

        return res

    def run_simulation(self, move, player):
        saved_board = deepcopy(self.board)
        saved_pieces = deepcopy(self.pieces)
        saved_player = self.cur_player
        saved_peace_counter = self.peace_counter

        self.do_move(move)

        result = self.den_distance_heuristic(player) + self.result_heuristic(player)

        self.board = saved_board
        self.pieces = saved_pieces
        self.cur_player = saved_player
        self.peace_counter = saved_peace_counter

        return result

    def run_simulations(self, moves, player):
        best_move = None
        best_res = -float("inf")
        for move in moves:
            res = self.run_simulation(move, player)
            if res > best_res:
                best_res = res
                best_move = move

        return best_move

    def best_move(self, player):
        moves = self.moves(player)
        return self.run_simulations(moves, player)

    # def update(self, player: int, move_string):
    #     assert player == self.curplayer
    #     move = tuple(int(m) for m in move_string.split())
    #     if len(move) != 4:
    #         raise WrongMove
    #     possible_moves = self.moves(player)
    #     if not possible_moves:
    #         if move != (-1, -1, -1, -1):
    #             raise WrongMove
    #         move = None
    #     else:
    #         move = ((move[0], move[1]), (move[2], move[3]))
    #         if move not in possible_moves:
    #             raise WrongMove
    #     self.do_move(move)
    #
    #     if self.victory(player):
    #         assert self.winner is not None
    #         return 2 * self.winner - 1
    #     else:
    #         return None


class Player(object):
    def __init__(self):
        self.game: Jungle = Jungle()
        self.my_player: int = 1
        self.say('RDY')

    def reset(self):
        self.game = Jungle()
        self.my_player = 1
        self.say('RDY')

    @staticmethod
    def say(what: str) -> None:
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    @staticmethod
    def hear() -> Tuple[str, List[str]]:
        line = sys.stdin.readline().split()
        return line[0], line[1:]

    def loop(self):
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                _unused_move_timeout, _unused_game_timeout = args[:2]
                move = tuple((int(m) for m in args[2:]))
                if move == (-1, -1, -1, -1):
                    move = None
                else:
                    xs, ys, xd, yd = move
                    move = (xs, ys), (xd, yd)

                self.game.do_move(move)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                #  assert not self.game.move_list
                self.my_player = 0

            moves = self.game.moves(self.my_player)
            if moves:
                move = self.game.best_move(self.my_player)
                self.game.do_move(move)
                move = (move[0][0], move[0][1], move[1][0], move[1][1])
            else:
                self.game.do_move(None)
                move = (-1, -1, -1, -1)
            self.say('IDO %d %d %d %d' % move)


if __name__ == '__main__':
    _player = Player()
    _player.loop()
