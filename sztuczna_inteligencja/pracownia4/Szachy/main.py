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

# def read_input():
#     return input().split()
#
#
# def send_output(output):
#     sys.stdout.flush()
#     print(output)
#     sys.stdout.flush()
#
#
# class Program:
#     if __name__ == '__main__':
#         send_output("RDY")
#         mcts = MCTS()
#         mcts_tree = Node(False, None, None, 1)
#
#         while True:
#             command = read_input()
#             if command[0] == "UGO":
#                 move_time = float(command[1])
#                 game_time = float(command[2])
#                 mcts_tree, m = mcts.next(Node(False, None, None, 0))
#                 send_output(f"IDO {m}")
#             elif command[0] == "HEDID":
#                 move_time = float(command[1])
#                 game_time = float(command[2])
#                 # opponents move
#                 opponent_move = command[3]
#                 mcts_tree = mcts.next_opponent(mcts_tree, opponent_move)
#                 # our move
#                 mcts_tree, m = mcts.next(mcts_tree)
#                 send_output(f"IDO {m}")
#             elif command[0] == "ONEMORE":
#                 send_output("RDY")
#                 reset_board()
#                 mcts_tree = Node(False, None, None, 1)
#             elif command[0] == "BYE":
#                 break
