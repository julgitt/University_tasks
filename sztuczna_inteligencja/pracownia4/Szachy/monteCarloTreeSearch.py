from sys import stderr
from time import time
from typing import Optional, Tuple, Dict
from math import sqrt, log
from random import choice

import chess

C = 1.0

board = chess.Board()


def reset_board():
    global board
    board = chess.Board()


class Node:

    def __init__(self, game_over: bool, parent: Optional['Node'], move: Optional[chess.Move], agent_player: int):
        self.children: Dict[chess.Move, Node] = {}
        self.heuristics_sum: int = 0
        self.visit_count: int = 0
        self.game_over: bool = game_over
        self.parent: Optional['Node'] = parent
        self.move: chess.Move = move
        self.agent_player: int = agent_player

    def ucb_score(self) -> float:
        if self.heuristics_sum == 0:
            return float("inf")

        return self.heuristics_sum / self.visit_count + C * sqrt(log(self.visit_count
                                                                     if not self.parent
                                                                     else self.parent.visit_count)
                                                                 / self.visit_count)

    def expand(self) -> None:
        if self.game_over:
            return

        children = {}
        legal_moves = board.legal_moves
        for m in legal_moves:
            board.push(m)
            children[m] = Node(board.is_game_over(), self, m, self.agent_player)
            board.pop()

        self.children = children

    def explore(self) -> None:
        current = self

        iterations = 0
        while current.children:
            children = current.children
            if not children:
                print("There are no children in explore", stderr)
            max_node_score = max(c.ucb_score() for c in children.values())
            moves = [a for a, c in children.items() if c.ucb_score() == max_node_score]
            move = choice(moves)
            board.push(move)
            current = children[move]
            iterations += 1

        if current.visit_count < 1:
            current.heuristics_sum += current.run_simulation()
        else:
            current.expand()
            if current.children:
                current = choice(list(current.children.values()))
                board.push(current.move)
                current.heuristics_sum += current.run_simulation()
                board.pop()
            else:
                current.heuristics_sum += current.run_simulation()

        current.visit_count += 1

        parent = current

        while parent.parent:
            parent = parent.parent
            parent.visit_count += 1
            parent.heuristics_sum += current.heuristics_sum

        for i in range(iterations):
            board.pop()

    def run_simulation(self) -> int:
        if self.game_over:
            return 0

        v = 0
        i = 0
        for i in range(20):
            if board.is_game_over():
                break
            move = choice(list(board.legal_moves))
            board.push(move)
            v += Node.heuristic(board, self.agent_player)
            i += 1
        for j in range(i):
            board.pop()
        return v

    def next(self) -> Tuple['Node', str]:
        if self.game_over:
            print("Game over in next", stderr)

        if not self.children:
            print("There are no children in next", stderr)

        children = self.children

        max_visit_count = max(node.visit_count for node in children.values())
        max_children = [c for a, c in children.items() if c.visit_count == max_visit_count]

        max_child = choice(max_children)
        max_child.parent = None
        board.push(max_child.move)

        return max_child, max_child.move.uci()

    def next_opponent(self, move: str) -> 'Node':
        if self.game_over:
            print("Game over in next_opponent", stderr)

        if not self.children:
            self.expand()

        children = self.children

        for m, child in list(children.items()):
            if m.uci() == move:
                child.parent = None
                board.push(m)
                return child

        print("Opponent has not found the move", stderr)

    @staticmethod
    def checkmate_heuristic(game: chess.Board, player: int) -> float:
        if game.is_checkmate():
            if game.turn == player:
                return -float("inf")
            return float("inf")
        return 0

    @staticmethod
    def mobility_heuristic(game: chess.Board, player: int) -> int:
        res = 0
        if game.legal_moves:
            for move in game.legal_moves:
                if game.color_at(move.from_square) == player:
                    res += 1
                else:
                    res -= 1
        return res

    @staticmethod
    def score_heuristic(game: chess.Board, player: int) -> int:
        piece_values = {
            chess.PAWN: 1,
            chess.KNIGHT: 3,
            chess.BISHOP: 3,
            chess.ROOK: 5,
            chess.QUEEN: 9
        }
        res = 0

        for square in chess.SQUARES:
            piece = game.piece_at(square)
            if piece:
                value = piece_values.get(piece.piece_type, 0)
                if piece.color == player:
                    res += value
                else:
                    res -= value
        return res

    @staticmethod
    def heuristic(game: chess.Board, player: int) -> float:
        return Node.score_heuristic(game, player) + 0.5 * Node.mobility_heuristic(game,
                                                                                  player) + Node.checkmate_heuristic(
            game, player)


class MCTS:
    def __init__(self):
        self.explores = 2

    def search(self, tree):
        start_time = time()
        explores = self.explores
        for i in range(explores):
            tree.explore()

        if time() - start_time > 0.5 and self.explores > 2:
            self.explores -= 1
        else:
            self.explores += 1

        return tree
