from time import time
import sys
from alphaBetaSearch import AlphaBetaSearch
from reversi import ReversiState


def read_input():
    return input().split()


def send_output(output):
    print(output)
    sys.stdout.flush()


class Program:
    if __name__ == "__main__":
        player = 1
        reversi = ReversiState()
        search = AlphaBetaSearch()
        moves = 0
        send_output("RDY")
        depth = 3
		
        while True:
            command = read_input()
            if command[0] == "UGO":
                player = 0
                move_time = float(command[1])
                game_time = float(command[2])
                m = reversi.best_move(player, search, depth)
                reversi.do_move(m, player)
                if m == None:
                	m = -1,-1
                send_output(f"IDO {m[0]} {m[1]}")
                moves += 1
            elif command[0] == "HEDID":
                move_time = float(command[1])
                game_time = float(command[2])
                # opponents move
                opponent_move = int(command[3]), int(command[4])
                if opponent_move != (-1, -1):
                	reversi.do_move(opponent_move, 1 - player)
                # our move
                m = reversi.best_move(player, search, depth)
                reversi.do_move(m, player)
                if m == None:
                	m = -1,-1
                send_output(f"IDO {m[0]} {m[1]}")
                moves += 1
            elif command[0] == "ONEMORE":
                send_output("RDY")
                player = 1

                reversi = ReversiState()
                search = AlphaBetaSearch()
            elif command[0] == "BYE":
                break
			
