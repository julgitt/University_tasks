from sys import stdout
import chess

from monteCarloTreeSearch import Node, reset_board, MCTS


def read_input():
    return input().split()


def send_output(output):
    stdout.flush()
    print(output)
    stdout.flush()


class Program:
    if __name__ == '__main__':
        tree = Node(False, None, None, chess.BLACK)
        mcts = MCTS()
        send_output("RDY")
        while True:
            command = input().split()
            if command[0] == "UGO":
                tree = Node(False, None, None, chess.WHITE)
                tree = mcts.search(tree)
                tree, move = tree.next()
                send_output(f"IDO {move}")
            elif command[0] == "HEDID":
                move = command[3]
                tree = tree.next_opponent(move)
                tree = mcts.search(tree)
                tree, move = tree.next()
                send_output(f"IDO {move}")
            elif command[0] == "ONEMORE":
                tree = Node(False, None, None, chess.BLACK)
                reset_board()
                send_output("RDY")
            elif command[0] == "BYE":
                break
