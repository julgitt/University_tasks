from collections import deque
from typing import List, Tuple, Set
from itertools import combinations


# region AC3
def ac3(domains: Tuple[List[List[int]], List[List[int]]]) -> bool:
    lines_queue = deque((False, i) for i in range(len(domains[False]))) \
                  + deque((1, i) for i in range(len(domains[True])))

    while lines_queue:
        is_column, line_idx = lines_queue.popleft()
        revised_indexes = revise_domains(is_column, line_idx, domains)
        if revised_indexes:
            for k in revised_indexes:
                if not domains[not is_column][k]:
                    return False
                lines_queue.append((not is_column, k))

    return True


def revise_domains(is_column: bool, idx: int, domains: Tuple[List[List[int]], List[List[int]]]) \
        -> Set[int]:
    cells_off, cells_on = get_certain_cells_for_line(is_column, idx, domains)
    indexes_to_revise = set()

    for line in domains[is_column][idx]:        # iterate lines from the given domain
        for idx2, neighbour_domain in enumerate(domains[not is_column]):
            is_cell_certain = (cells_off >> idx2) & 1 == (cells_on >> idx2) & 1
            if is_cell_certain:
                for neighbour_line in list(neighbour_domain):
                    if (line >> idx2) & 1 != (neighbour_line >> idx) & 1:
                        neighbour_domain.remove(neighbour_line)
                        if not neighbour_domain:
                            return {idx2}
                        indexes_to_revise.add(idx2)

    return indexes_to_revise
# endregion


# region AC3 Helper
def get_certain_cells_for_line(is_column: bool, line_idx: int,
                                     domains: Tuple[List[List[int]], List[List[int]]]) -> Tuple[int, int]:
    if not domains[is_column][line_idx]:
        return 0, 0

    cells_on = domains[is_column][line_idx][0]
    cells_off = domains[is_column][line_idx][0]

    for line in domains[is_column][line_idx][1:]:
        cells_on &= line
        cells_off |= line

    return cells_off, cells_on


# endregion


# region Solve
def solve_nonogram(row_constraints: List[List[int]], column_constraints: List[List[int]], height: int, width: int) \
        -> List[int]:
    domains = initialize_domains(width, height, row_constraints, column_constraints)

    if not ac3(domains):
        exit(1)

    solved_nonogram = generate_nonogram_from_domains(domains)
    return solved_nonogram


# endregion


# region Nonogram Operations
def generate_nonogram_from_domains(domains: Tuple[List[List[int]], List[List[int]]]) -> List[int]:
    return [row_domain[0] for row_domain in domains[0]]
# endregion


# region Domain
def initialize_domains(row_len: int, col_len: int, row_constraints: List[List[int]], col_constraints: List[List[int]]) \
        -> Tuple[List[List[int]], List[List[int]]]:
    row_domains = [generate_valid_lines(row_len, desc) for desc in row_constraints]
    col_domains = [generate_valid_lines(col_len, desc) for desc in col_constraints]
    return row_domains, col_domains


def generate_valid_lines(line_len: int, block_lengths: List[int]) -> List[int]:
    def is_valid_line(blocks_start_indexes: Tuple[int, ...]) -> bool:
        for i, start_id in enumerate(blocks_start_indexes):
            if start_id + block_lengths[i] > line_len:
                return False
            if i + 1 < len(block_lengths) and start_id + block_lengths[i] + 1 > blocks_start_indexes[i + 1]:
                return False
        return True

    def generate_line(blocks_start_ids: Tuple[int, ...]) -> int:
        line = 0
        for start_id, length in zip(blocks_start_ids, block_lengths):
            for j in range(length):
                line |= (1 << (start_id + j))
        return line

    all_combinations = combinations(range(line_len), len(block_lengths))
    valid_combinations = filter(is_valid_line, all_combinations)
    generated_lines = list(map(generate_line, valid_combinations))
    return generated_lines
# endregion


def main():
    with open("zad_input.txt", 'r') as file:
        height, width = map(int, file.readline().split())
        rows_desc = [list(map(int, file.readline().strip().split())) for _ in range(height)]
        col_desc = [list(map(int, file.readline().strip().split())) for _ in range(width)]

    result = solve_nonogram(rows_desc, col_desc, height, width)

    with open("zad_output.txt", "w", encoding='utf-8') as output_file:
        for line in result:
            new_line = ""
            binary_string = format(line, f"0{width}b")
            binary_line = [int(bit) for bit in binary_string]
            binary_line.reverse()
            for i in range(len(binary_line)):
                new_line += ("#" if binary_line[i] else ".")

            output_file.write(new_line + "\n")


if __name__ == "__main__":
    main()
