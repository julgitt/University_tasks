from typing import List    
from argparse import ArgumentParser

from board import Board 
from piece import King, Rook 
from solver import Solver


def read_input_from_file(filename: str) -> List[Board]:
    boards = []
    try:
        with open(filename, 'r') as file:
            for line in file:
                data = line.strip().split()
                if len(data) == 4:
                    player_color, white_king_pos, white_rook_pos, black_king_pos = data
                    board = Board(player_color, King(white_king_pos), Rook(white_rook_pos), King(black_king_pos))
                    boards.append(board)
                else:
                    print("Incorrect format of the input")
    except FileNotFoundError:
        print(f"File '{filename}' does not exist")
    return boards


def main():
    parser = ArgumentParser()
    parser.add_argument('--debug', action='store_true', help='Run in debug mode')
    args = parser.parse_args()
    
    input_file = "zad1_input.txt"
    output_file = "zad1_output.txt"
    
    chess_endgames = read_input_from_file(input_file)
    if chess_endgames:
        with open(output_file, "w") as output_file:
            for endgame in chess_endgames:
                solver = Solver(endgame)
                move_count, moves = solver.solve()
                if args.debug: 
                    print(moves + "\n")
                output_file.write(move_count + "\n")


if __name__ == "__main__":
    main()
