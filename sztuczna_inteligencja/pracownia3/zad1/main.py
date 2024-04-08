from collections import deque
from typing import List, Tuple, Set
from itertools import combinations

# region AC3
def ac3(domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) -> bool:
    queue = deque()
    for i in range(len(domains[0])):
        queue.append((0, i))

    for i in range(len(domains[1])):
        queue.append((1, i))

    while queue:
        is_col, index = queue.popleft()
        to_revise = revise(is_col, index, domains)
        if to_revise:
            if not domains[is_col][index]:
                return False
            for k in to_revise:
                queue.append((not is_col, k))

    return True


def revise(is_column: bool, index: int, domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) -> Set[int]:
    certain_indexes = get_line_certain_indexes(is_column, index, domains)
    indexes_to_revise = set()

    for line in domains[is_column][index]:
        for other_index, _ in enumerate(domains[not is_column]):
            if other_index in certain_indexes:
                not_satisfies = False
                for other_line in list(domains[not is_column][other_index]):
                    if line[other_index] != other_line[index]:
                        domains[not is_column][other_index].remove(other_line)
                        not_satisfies = True
                if not_satisfies:
                    indexes_to_revise.add(other_index)

    return indexes_to_revise
# endregion


# region AC3 Helper
def get_line_certain_indexes(is_col: bool, idx: int,
                             domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) -> Set[int]:
    if not domains[is_col][idx]:
        return set()

    line_cells_on = {i for i, bit in enumerate(domains[is_col][idx][0]) if bit == 1}
    line_cells_off = {i for i, bit in enumerate(domains[is_col][idx][0]) if bit == 0}

    for example_solution in domains[is_col][idx][1:]:
        for i, bit in enumerate(example_solution):
            if bit == 1:
                line_cells_off.discard(i)
            elif bit == 0:
                line_cells_on.discard(i)

    return line_cells_on.union(line_cells_off)
# endregion


# region Solve
def solve(rows_descriptions: List[List[int]], cols_descriptions: List[List[int]], height: int, width: int) \
        -> List[List[int]]:
    domains = generate_initial_domains(width, height, rows_descriptions, cols_descriptions)

    if not ac3(domains):
        exit(1)
    nonogram = generate_nonogram(domains)
    return nonogram
# endregion


# region Nonogram Operations
def generate_nonogram(domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) -> List[List[int]]:
    return [row[0] for row in domains[0]]
# endregion


# region Domain
def generate_initial_domains(row_len: int, col_len: int, row_desc: List[List[int]], col_desc: List[List[int]]) \
        -> Tuple[List[List[List[int]]], List[List[List[int]]]]:
    row_domains = [get_all_valid_lines(row_len, desc) for desc in row_desc]
    col_domains = [get_all_valid_lines(col_len, desc) for desc in col_desc]
    return row_domains, col_domains


def get_all_valid_lines(line_len: int, blocks_desc: List[int]) -> List[List[int]]:
    def is_valid_line(blocks_start_ids: Tuple[int, ...]) -> bool:
        for i, start_id in enumerate(blocks_start_ids):
            if start_id + blocks_desc[i] > line_len:
                return False
            if i + 1 < len(blocks_desc) and start_id + blocks_desc[i] + 1 > blocks_start_ids[i + 1]:
                return False
        return True

    def generate_line(blocks_start_ids: Tuple[int, ...]) -> List[int]:
        line = [0] * line_len
        for start_id, length in zip(blocks_start_ids, blocks_desc):
            for j in range(length):
                line[start_id + j] = 1
        return line

    all_combinations = combinations(range(line_len), len(blocks_desc))
    valid_combinations = filter(is_valid_line, all_combinations)
    return [generate_line(comb) for comb in valid_combinations]


# endregion


def main():
    with open("zad_input.txt", 'r') as file:
        height, width = map(int, file.readline().split())
        rows_desc = [list(map(int, file.readline().strip().split())) for _ in range(height)]
        col_desc = [list(map(int, file.readline().strip().split())) for _ in range(width)]

    result = solve(rows_desc, col_desc, height, width)

    with open("zad_output.txt", "w", encoding='utf-8') as output_file:
        for line in result:
            new_line = ""
            for i in range(len(line)):
                new_line += ("#" if line[i] else ".")

            output_file.write(new_line + "\n")


if __name__ == "__main__":
    main()
