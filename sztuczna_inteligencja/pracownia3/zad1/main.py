from collections import deque
from typing import List, Tuple, Set
from itertools import combinations


# region AC3
def ac3(domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) -> bool:
    lines_queue = deque()
    for i in range(len(domains[0])):
        lines_queue.append((0, i))

    for i in range(len(domains[1])):
        lines_queue.append((1, i))

    while lines_queue:
        is_column, line_idx = lines_queue.popleft()
        revised_indexes = revise_domains(is_column, line_idx, domains)
        if revised_indexes:
            for k in revised_indexes:
                if len(domains[not is_column][k]) == 0:
                    return False
                lines_queue.append((not is_column, k))

    return True


def revise_domains(is_column: bool, line_idx: int, domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) \
        -> Set[int]:
    constrained_indexes = get_constrained_indexes_for_line(is_column, line_idx, domains)
    indexes_to_revise = set()

    for line in domains[is_column][line_idx]:
        for other_line_idx, _ in enumerate(domains[not is_column]):
            if other_line_idx in constrained_indexes:  # index is correct
                revised = False
                for other_line in list(domains[not is_column][other_line_idx]):
                    if line[other_line_idx] != other_line[line_idx]:
                        domains[not is_column][other_line_idx].remove(other_line)
                        if len(domains[not is_column][other_line_idx]) == 0:
                            return {other_line_idx}
                        revised = True

                if revised:
                    indexes_to_revise.add(other_line_idx)

    return indexes_to_revise
# endregion


# region AC3 Helper
def get_constrained_indexes_for_line(is_column: bool, line_idx: int,
                                     domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) -> Set[int]:
    if not domains[is_column][line_idx]:
        return set()

    set_of_cells_on = {i for i, bit in enumerate(domains[is_column][line_idx][0]) if bit == 1}
    set_of_cells_off = {i for i, bit in enumerate(domains[is_column][line_idx][0]) if bit == 0}

    for example_solution in domains[is_column][line_idx][1:]:
        for i, bit in enumerate(example_solution):
            if bit == 1:
                set_of_cells_off.discard(i)
            elif bit == 0:
                set_of_cells_on.discard(i)

    return set_of_cells_on.union(set_of_cells_off)


# endregion


# region Solve
def solve_nonogram(row_constraints: List[List[int]], column_constraints: List[List[int]], height: int, width: int) \
        -> List[List[int]]:
    domains = initialize_domains(width, height, row_constraints, column_constraints)

    if not ac3(domains):
        exit(1)

    solved_nonogram = generate_nonogram_from_domains(domains)
    return solved_nonogram


# endregion


# region Nonogram Operations
def generate_nonogram_from_domains(domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) -> List[List[int]]:
    return [row_domain[0] for row_domain in domains[0]]
# endregion


# region Domain
def initialize_domains(row_len: int, col_len: int, row_constraints: List[List[int]], col_constraints: List[List[int]]) \
        -> Tuple[List[List[List[int]]], List[List[List[int]]]]:
    row_domains = [generate_valid_lines(row_len, desc) for desc in row_constraints]
    col_domains = [generate_valid_lines(col_len, desc) for desc in col_constraints]
    return row_domains, col_domains


def generate_valid_lines(line_len: int, block_lengths: List[int]) -> List[List[int]]:
    def is_valid_line(blocks_start_indexes: Tuple[int, ...]) -> bool:
        for i, start_id in enumerate(blocks_start_indexes):
            if start_id + block_lengths[i] > line_len:
                return False
            if i + 1 < len(block_lengths) and start_id + block_lengths[i] + 1 > blocks_start_indexes[i + 1]:
                return False
        return True

    def generate_line(blocks_start_ids: Tuple[int, ...]) -> List[int]:
        line = [0] * line_len
        for start_id, length in zip(blocks_start_ids, block_lengths):
            for j in range(length):
                line[start_id + j] = 1
        return line

    all_combinations = combinations(range(line_len), len(block_lengths))
    valid_combinations = filter(is_valid_line, all_combinations)
    return [generate_line(comb) for comb in valid_combinations]
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
            for i in range(len(line)):
                new_line += ("#" if line[i] else ".")

            output_file.write(new_line + "\n")


if __name__ == "__main__":
    main()
