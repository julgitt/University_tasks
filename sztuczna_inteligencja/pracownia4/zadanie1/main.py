from time import time
import sys
from alphaBetaSearch import AlphaBetaSearch
from reversi import ReversiState


class Program:
    if __name__ == "__main__":
        lost = 0

        agent_player = 0
        start_t = time()
        search = AlphaBetaSearch()
        for i in range(1000):
            board = ReversiState()
            move_count = 0
            player = agent_player
            while True:
                # state.draw()
                # state.show()
                # print(player)
                depth = (move_count**2 // 500) + 1
                if player == agent_player:
                    m = board.best_move(player, search, depth)
                else:
                    m = board.random_move(player)
                board.do_move(m, player)
                move_count += 1
                player = 1 - player
                # input()
                if board.terminal():
                    break

            # board.draw()
            # board.show()
            print(f'Result: {board.result()}, depth: {depth}')
            if board.result() > 0 and agent_player == 0:
                lost += 1
            elif board.result() < 0 and agent_player == 1:
                lost += 1

            agent_player = 1 - agent_player
        end_t = time()
        print(f'{lost}, time: {end_t - start_t}')
        # input()
        sys.exit(0)

