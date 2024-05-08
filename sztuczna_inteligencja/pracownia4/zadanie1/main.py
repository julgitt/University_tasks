from time import time
import sys
from alphaBetaSearch import AlphaBetaSearch
from reversi import ReversiState


class Program:
    if __name__ == "__main__":
        lost_games = 0
        agent_player = 0
        start_t = time()
        search = AlphaBetaSearch()

        for i in range(1000):
            reversi = ReversiState()
            move_count = 0
            player = agent_player

            while True:
                # state.draw()

                depth = (move_count**2 // 500) + 1

                if player == agent_player:
                    m = reversi.best_move(player, search, depth)
                else:
                    m = reversi.random_move(player)

                reversi.do_move(m, player)

                move_count += 1
                player = 1 - player

                if reversi.terminal():
                    break

            # board.draw()
            # print(f'Result: {reversi.result()}, depth: {depth}')
            if (reversi.result() > 0 and agent_player == 0) or (reversi.result() < 0 and agent_player == 1):
                lost_games += 1

            agent_player = 1 - agent_player

        end_t = time()
        print(f'lost_games: {lost_games}, time: {end_t - start_t}')
        sys.exit(0)

