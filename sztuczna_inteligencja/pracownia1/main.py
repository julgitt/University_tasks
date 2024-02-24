from typing import List    
from argparse import ArgumentParser

from board import Board 
from piece import King, Rook 
from solver import Solver


def read_input_from_file(filename: str) -> List[Board]:
    with open(filename, 'r') as file:
        lines = file.readlines()
        boards = []
        for line in lines:
            data = line.strip().split()
            player_color, white_king_pos, white_rook_pos, black_king_pos = data
            board = Board(player_color, King(white_king_pos), Rook(white_rook_pos), King(black_king_pos))
            boards.append(board)
    return boards


def main():
    parser = ArgumentParser()
    parser.add_argument('--debug', action='store_true', help='Uruchom w trybie debug')
    args = parser.parse_args()
    
    chess_endgames = read_input_from_file("zad1_input.txt")
    with open("zad1_output.txt", "w") as output_file:
        for endgame in chess_endgames:
            solver = Solver(endgame)
            result = solver.solve()
            if args.debug: 
                print(result[1] + "\n")
            output_file.write(result[0] + "\n")


if __name__ == "__main__":
    main()
