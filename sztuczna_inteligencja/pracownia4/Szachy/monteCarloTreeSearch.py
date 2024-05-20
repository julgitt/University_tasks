from random import choice
from typing import Optional, Tuple
from math import sqrt, log
from copy import deepcopy
import chess
from time import time
C = 1.5


class Node:
    def __init__(self, state: chess.Board, done: bool, parent, action, player: int, agent):
        self.children: dict = {}
        self.total_reward: int = 0
        self.visit_count: int = 0
        self.game: chess.Board = state
        self.done: bool = done
        self.parent: Optional[Node] = parent
        self.action = action
        self.player = player
        self.agent = agent

    def get_ucb_score(self) -> float:
        if self.visit_count == 0:
            return float("inf")

        top_node = self
        if top_node.parent:
            top_node = top_node.parent

        return self.total_reward / self.visit_count + 1.5 * sqrt(log(top_node.visit_count) / self.visit_count)

    def expand(self):
        if self.done:
            return

        children = {}
        moves = self.game.legal_moves
        for move in moves:
            new_game = deepcopy(self.game)
            new_game.push(move)
            children[move] = Node(new_game, new_game.is_game_over(), self, move, 1 - self.player, self.agent)

        self.children = children

    def explore(self) -> None:
        current = self

        while current.children:
            children = current.children
            max_score = max(c.get_ucb_score() for c in children.values())
            actions = [a for a, c in children.items() if c.get_ucb_score() == max_score]
            if len(actions) == 0:
                print("error zero length ", max_score)
            action = choice(actions)
            current = children[action]

        if current.visit_count < 1:
            current.total_reward += current.simulation()
        else:
            current.create_children()
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
        while not new_game.is_game_over():
            action = choice(list(new_game.legal_moves))
            new_game.push(action)
            if self.agent == 1:
                v += Node.heuristic(new_game)
            else:
                v -= Node.heuristic(new_game)

        return v

    def next(self):
        if self.done:
            raise ValueError("game has ended")

        if not self.children:
            raise ValueError('no children found and game hasn\'t ended')

        children = self.children

        max_visit_count = max(node.visit_count for node in children.values())

        max_children = [c for a, c in children.items() if c.visit_count == max_visit_count]

        if len(max_children) == 0:
            print("error zero length ", max_visit_count)

        max_child = choice(max_children)

        max_child.parent = None

        return max_child, max_child.move.uci()

    def next_opponent(self, move):
        if self.done:
            raise ValueError("game has ended")

        #if not self.children:
        #    self.extend()

        if not self.children:
            new_state = deepcopy(self.game)
            if move != (-1, -1):
                new_state.push(move)
            self.children[move] = Node(new_state, new_state.is_game_over(), self, move, 1 - self.player, self.agent)

        children = self.children

        for m, c in list(children.keys()):
            if m.uci() == move:
                children[m].parent = None
                return children[m]

        raise ValueError("Move is not possible")

    @staticmethod
    def heuristic(game: chess.Board, player: int):
        return 0

        # piece_values = {
        #     chess.PAWN: 1,
        #     chess.KNIGHT: 3,
        #     chess.BISHOP: 3,
        #     chess.ROOK: 5,
        #     chess.QUEEN: 9
        # }
        #
        # white_material = 0
        # black_material = 0
        #
        # for square in chess.SQUARES:
        #     piece = game.piece_at(square)
        #     if piece:
        #         value = piece_values.get(piece.piece_type, 0)
        #         if piece.color == chess.WHITE:
        #             white_material += value
        #         else:
        #             black_material += value
        # if player == 0:
        #     return white_material - black_material
        #
        # return black_material - white_material


class MCTS:
    def __init__(self, explores: int = 100):
        self.explores = explores

    @staticmethod
    def next(tree: Node) -> Tuple[Node, Tuple[int, int]]:
        start = time()
        while time() - start < 0.45:
            tree.explore()

        next_tree, next_action = tree.next()

        return next_tree, next_action

    @staticmethod
    def next_opponent(tree: Node, move: Tuple[int, int]) -> Node:
        next_tree = tree.next_opponent(move)

        return next_tree
