from time import time
from math import sqrt, log
from random import choice
from typing import Tuple, Optional, Dict
from copy import deepcopy

C = 1.4


class Node:
    def __init__(self, board, game_over: bool, parent: Optional['Node'],
                 move: Tuple[int, int], player: int, agent_player: int):
        self.board = board
        self.children: Dict[Tuple[int, int], Node] = {}
        self.heuristics_sum: int = 0
        self.visit_count: int = 0
        self.game_over: bool = game_over
        self.parent: Optional[Node] = parent
        self.move: Tuple[int, int] = move
        self.player: int = player
        self.agent_player: int = agent_player

    def ucb_score(self) -> float:
        if self.visit_count == 0:
            return float("inf")

        parent_visits = self.parent.visit_count if self.parent else self.visit_count
        return self.heuristics_sum / self.visit_count + C * sqrt(log(parent_visits) / self.visit_count)

    def expand(self) -> None:
        if self.game_over:
            return

        children = {}
        moves = self.board.moves(self.player)
        for move in moves:
            new_game = deepcopy(self.board)
            new_game.do_move(move, self.player)
            if move is None:
                move = (-1, -1)
            children[move] = Node(new_game, new_game.terminal(), self, move, 1 - self.player, self.agent_player)

        self.children = children

    def explore(self) -> None:
        current = self

        while current.children:
            children = current.children
            max_score = max(c.ucb_score() for c in children.values())
            moves = [a for a, c in children.items() if c.ucb_score() == max_score]
            move = choice(moves)
            current = children[move]

        if current.visit_count < 1:
            current.heuristics_sum += current.run_simulation()
        else:
            current.expand()
            if current.children:
                current = choice(list(current.children.values()))
            current.heuristics_sum += current.run_simulation()

        current.visit_count += 1

        parent = current

        while parent.parent:
            parent = parent.parent
            parent.visit_count += 1
            parent.heuristics_sum += current.heuristics_sum

    def run_simulation(self) -> int:
        if self.game_over:
            return 0

        total_value = 0
        for i in range(7):
            new_game = deepcopy(self.board)
            player = self.player
            while not new_game.terminal():
                move = choice(new_game.moves(player))
                new_game.do_move(move, player)
                player = 1 - player

            total_value += new_game.heuristic(self.agent_player)

        return total_value

    def next(self) -> Tuple['Node', Tuple[int, int]]:
        if self.game_over:
            raise ValueError("Game over in next")

        if not self.children:
            raise ValueError("There are no children in next")

        max_visit_count = max(node.visit_count for node in self.children.values())
        best_children = [c for a, c in self.children.items() if c.visit_count == max_visit_count]
        best_child = choice(best_children)
        best_child.parent = None

        return best_child, best_child.move

    def next_opponent(self, move: Tuple[int, int]) -> 'Node':
        if self.game_over:
            raise ValueError("Game over in next_opponent")

        if not self.children:
            self.expand()

        children = self.children
        for m, child in children.items():
            if m == move:
                child.parent = None
                return child

        raise ValueError("Opponent move not found")


class MCTS:
    def __init__(self):
        self.explores = 100

    @staticmethod
    def search(tree: Node) -> Node:
        start = time()
        while time() - start < 0.5:
            tree.explore()

        return tree
