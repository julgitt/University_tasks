from time import time
from math import sqrt, log
from random import choice
from typing import Tuple, Optional, Dict
from reversi import ReversiState
from copy import deepcopy
import sys


class Node:
    def __init__(self, state: ReversiState, done: bool, parent: Optional['Node'], action: Tuple[int, int], player: int, agent: int):
        self.children: Dict[Tuple[int, int], Node] = {}
        self.total_reward: int = 0
        self.visit_count: int = 0
        self.state: ReversiState = state
        self.done: bool = done
        self.parent: Optional[Node] = parent
        self.action: Tuple[int, int] = action
        self.player: int = player
        self.agent: int = agent

    def get_ucb_score(self) -> float:
        if self.visit_count == 0:
            return float("inf")

        top_node = self
        if top_node.parent:
            top_node = top_node.parent

        return self.total_reward / self.visit_count + 2 * sqrt(log(top_node.visit_count) / self.visit_count)

    def expand(self) -> None:
        if self.done:
            return

        children = {}
        moves = self.state.moves(self.player)
        for move in moves:
            new_game = deepcopy(self.state)
            new_game.do_move(move, self.player)
            if move is None:
                move = (-1, -1)
            children[move] = Node(new_game, new_game.terminal(), self, move, 1 - self.player, self.agent)

        self.children = children

    def explore(self) -> None:
        current = self

        while current.children:
            children = current.children
            max_score = max(c.get_ucb_score() for c in children.values())
            actions = [a for a, c in children.items() if c.get_ucb_score() == max_score]
            if len(actions) == 0:
                print(f"error zero length: {max_score}", sys.stderr)
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

    def simulation(self) -> int:
        if self.done:
            return 0
        v = 0
        new_game = deepcopy(self.state)
        player = self.player
        # for i in range(20):
        #     if new_game.terminal():
        #         break
        while not new_game.terminal():
            action = choice(new_game.moves(player))
            new_game.do_move(action, player)
            if self.agent == 1:
                v += new_game.heuristic()
            else:
                v -= new_game.heuristic()
            player = 1 - player

        return v

    def next(self) -> Tuple['Node', Tuple[int, int]]:
        if self.done:
            raise ValueError("game has ended")

        if not self.children:
            raise ValueError("game hasn't ended")

        children = self.children

        max_visited = max(node.visit_count for node in children.values())

        max_children = [c for a, c in children.items() if c.visit_count == max_visited]

        if len(max_children) == 0:
            print("error zero length", sys.stderr)

        max_child = choice(max_children)

        max_child.parent = None

        return max_child, max_child.action

    def next_opponent(self, move: Tuple[int, int]) -> 'Node':
        if self.done:
            raise ValueError("game has ended")

        if not self.children:
            self.expand()

        children = self.children

        for m, c in children.items():
            if m == move:
                c.parent = None
                return c

        raise ValueError("Move is not possible")


class MCTS:
    def __init__(self, explores: int = 100):
        self.explores = explores

    @staticmethod
    def next(tree: Node) -> Tuple[Node, Tuple[int, int]]:
        start = time()
        while time() - start < 0.5:
            tree.explore()

        next_tree, next_action = tree.next()

        return next_tree, next_action

    @staticmethod
    def next_opponent(tree: Node, move: Tuple[int, int]) -> Node:
        next_tree = tree.next_opponent(move)

        return next_tree
