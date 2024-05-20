from math import sqrt
from time import time
import sys
from alphaBetaSearch import AlphaBetaSearch
from reversi import ReversiState

GAMES = 1000


class Program:
    if __name__ == "__main__":
        lost_games = 0
        agent_player = 0
        start_t = time()
        search = AlphaBetaSearch()

        for i in range(GAMES):
            reversi = ReversiState()
            move_count = 0
            current_player = 0

            while True:
                # state.draw()
                depth = move_count**2 // 500 + 1

                if current_player == agent_player:
                    m = reversi.best_move(current_player, search, depth)
                else:
                    m = reversi.random_move(current_player)

                reversi.do_move(m, current_player)

                move_count += 1
                current_player = 1 - current_player

                if reversi.terminal():
                    break

            # board.draw()
            print(f'Result: {reversi.result()}, depth: {depth}, moves: {move_count} ')
            if (reversi.result() > 0 and agent_player == 0) or (reversi.result() < 0 and agent_player == 1):
                lost_games += 1

            agent_player = 1 - agent_player

        end_t = time()
        print(f'lost_games: {lost_games} / {GAMES}, time: {end_t - start_t}')
        sys.exit(0)

