from sys import exit
from time import time

from alphaBetaSearch import AlphaBetaSearch
from reversi import ReversiState

GAMES = 1000


class Program:
    if __name__ == "__main__":
        lost_games = 0
        agent_player = 0
        start_time = time()
        search = AlphaBetaSearch()

        for i in range(GAMES):
            reversi = ReversiState()
            move_count = 0
            current_player = 0

            while True:
                # state.draw()
                depth = move_count**2 // 500 + 1

                if current_player == agent_player:
                    move = reversi.best_move(current_player, search, depth)
                else:
                    move = reversi.random_move(current_player)

                reversi.do_move(move, current_player)
                move_count += 1
                current_player = 1 - current_player

                if reversi.terminal():
                    break

            # board.draw()
            result = reversi.result()
            print(f'Result: {result}, depth: {depth}, moves: {move_count} ')
            if (result > 0 and agent_player == 0) or (result < 0 and agent_player == 1):
                lost_games += 1

            agent_player = 1 - agent_player

        end_time = time()
        print(f'lost_games: {lost_games} / {GAMES}, time: {end_time - start_time:.2f}')
        exit(0)

