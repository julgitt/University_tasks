from random import choice
from typing import Optional, Tuple
from math import sqrt, log
from copy import deepcopy
import chess
from time import time
C = 1.5


class Node:
    def __init__(self, state: chess.Board, done: bool, parent: Optional['Node'],
                 action: Optional[chess.Move], agent: chess.COLORS):
        self.children: dict = {}
        self.total_reward: int = 0
        self.visit_count: int = 0
        self.game: chess.Board = state
        self.done: bool = done
        self.parent: Optional[Node] = parent
        self.action: chess.Move = action
        self.agent: int = agent

    def get_ucb_score(self) -> float:
        if self.visit_count == 0:
            return float("inf")

        top_node = self
        if top_node.parent:
            top_node = top_node.parent

        return self.total_reward / self.visit_count + 1 * sqrt(log(top_node.visit_count) / self.visit_count)

    def expand(self) -> None:
        if self.done:
            return

        children = {}
        moves = self.game.legal_moves
        for move in moves:
            new_game = deepcopy(self.game)
            new_game.push(move)
            children[move] = Node(new_game, new_game.is_game_over(), self, move, self.agent)

        self.children = children

    def explore(self) -> None:
        current = self

        while current.children:
            children = current.children
            max_score = max(c.get_ucb_score() for c in children.values())
            actions = [a for a, c in children.items() if c.get_ucb_score() == max_score]
            if not actions:
                print("error zero length ", max_score)
            action = choice(actions)
            current = children[action]

        if current.visit_count < 1:
            current.total_reward += current.simulation()
        else:
            current.expand()
            if current.children:
                current = choice(list(current.children.values()))
            current.total_reward += current.simulation()

        current.visit_count += 1

        parent = current

        while parent.parent:
            parent = parent.parent
            parent.visit_count += 1
            parent.total_reward += current.total_reward

    def simulation(self):
        if self.done:
            return 0
        v = 0
        new_game = deepcopy(self.game)
        for _ in range(20):
            if new_game.is_game_over():
                break
            action = choice(list(new_game.legal_moves))
            new_game.push(action)
            v += heuristic(new_game, self.agent)

        return v

    def next(self) -> Tuple['Node', str]:
        if self.done:
            raise ValueError("game has ended")

        if not self.children:
            raise ValueError('no children found and game hasn\'t ended')

        children = self.children

        max_visit_count = max(node.visit_count for node in children.values())

        max_children = [c for a, c in children.items() if c.visit_count == max_visit_count]

        #if len(max_children) == 0:
        #    print("error zero length ", max_visit_count)

        max_child = choice(max_children)

        max_child.parent = None

        return max_child, max_child.action.uci()

    def next_opponent(self, move: str) -> 'Node':
        if self.done:
            raise ValueError("game has ended")

        if not self.children:
            self.expand()

        children = self.children

        for m, c in list(children.items()):
            if m.uci() == move:
                c.parent = None
                return c

        raise ValueError("Move is not possible")


def check(game: chess.Board, player: chess.COLORS) -> float:
    if game.is_checkmate():
        if game.turn == player:
            return -float("inf")
        return float("inf")
    return 0


def mobility(game: chess.Board, player: chess.COLORS) -> int:
    res = 0
    if game.legal_moves:
        for move in game.legal_moves:
            if game.color_at(move.from_square) == player:
                res += 1
            else:
                res -= 1
    return res


def score_heuristic(game: chess.Board, player: chess.COLORS) -> int:
    piece_values = {
        chess.PAWN: 1,
        chess.KNIGHT: 3,
        chess.BISHOP: 3,
        chess.ROOK: 5,
        chess.QUEEN: 9
    }
    white = 0
    black = 0

    for square in chess.SQUARES:
        piece = game.piece_at(square)
        if piece:
            value = piece_values.get(piece.piece_type, 0)
            if piece.color == chess.WHITE:
                white += value
            else:
                black += value
    if player == 0:
        return white - black

    return black - white


def heuristic(game: chess.Board, player: int) -> float:
    return score_heuristic(game, player) + 0.5 * mobility(game, player) + check(game, player)


class MCTS:
    def __init__(self, explores: int = 100):
        self.explores = explores

    @staticmethod
    def next(tree: Node) -> Tuple[Node, str]:
        start = time()
        while time() - start < 0.60:
        #for i in range(100):
            tree.explore()

        next_tree, next_action = tree.next()

        return next_tree, next_action

    @staticmethod
    def next_opponent(tree: Node, move: str) -> Node:
        next_tree = tree.next_opponent(move)

        return next_tree
