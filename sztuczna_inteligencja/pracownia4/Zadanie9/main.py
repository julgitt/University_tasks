from time import time
import sys
from monteCarloTreeSearch import MCTS, Node
from reversi import ReversiState


def read_input():
    return input().split()


def send_output(output):
    sys.stdout.flush()
    print(output)
    sys.stdout.flush()


class Program:
    if __name__ == "__main__":
        send_output("RDY")
        reversi = ReversiState()
        mcts = MCTS()
        mcts_tree = Node(reversi, False, None, (0, 0), 0, 1)

        while True:
            command = read_input()
            if command[0] == "UGO":
                mcts_tree = Node(reversi, False, None, (0, 0), 0, 0)
                mcts_tree = mcts.search(mcts_tree)
                mcts_tree, m = mcts_tree.next()
                send_output(f"IDO {m[0]} {m[1]}")
            elif command[0] == "HEDID":
                # opponents move
                opponent_move = int(command[3]), int(command[4])
                mcts_tree = mcts_tree.next_opponent(opponent_move)
                # our move
                mcts_tree = mcts.search(mcts_tree)
                mcts_tree, m = mcts_tree.next()
                send_output(f"IDO {m[0]} {m[1]}")
            elif command[0] == "ONEMORE":
                send_output("RDY")
                reversi = ReversiState()
                mcts_tree = Node(reversi, False, None, (0, 0), 0, 1)
            elif command[0] == "BYE":
                break
