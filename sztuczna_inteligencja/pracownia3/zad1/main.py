from collections import deque
from typing import List, Tuple, Set
import itertools


def ac3(domains: Tuple[List[List[List[int]]], List[List[List[int]]]]) -> bool:
    queue = deque()
    for i in range(len(domains[0])):
        queue.append((0, i))

    for i in range(len(domains[1])):
        queue.append((1, i))

    while queue:
        is_col, index = queue.popleft()
        is_revised, revised_indexes = revise(is_col, index, domains)
        if is_revised:
            if len(domains[is_col]) == 0:
                return False
            for k in revised_indexes:
                queue.append((not is_col, k))
            queue.append((is_col, index))

    for domain in domains[0]:
        print(len(domain))
    return True


def revise(is_col, idx, domains) -> Tuple[bool, Set[int]]:
    revised = False
    all_not_certain_cells_after = get_all_line_uncertain_indexes(domains, is_col, idx)
    # all_definite_on_cells_after, all_definite_off_cells_after = get_all_line_definite_cells(domains, is_col, idx)

    for line_from_domain in list(domains[is_col][idx]):  # bierzemy przykładową linijkę z dziedziny, np wiersz
        for idx2 in range(len(list(domains[not is_col]))):  # iterujemy się po kolejnych np kolumnach
            satisfies = False
            for line_from_domain2 in list(domains[not is_col][idx2]):  # bierzemy jakies rozwiazanie np kolumny
                if line_from_domain[idx2] == line_from_domain2[idx]:  # sprawdzamy czy pasi
                    satisfies = True
                    break
            if not satisfies:
                domains[is_col][idx].remove(line_from_domain)
                revised = True
                break

    all_not_certain_cells_after = get_all_line_uncertain_indexes(domains, is_col, idx)
    # all_definite_on_cells_after, all_definite_off_cells_after = get_all_line_definite_cells(domains, is_col, idx)

    return revised, all_not_certain_cells_after


# region AC3 Helper
def get_all_line_definite_cells(domains, is_col, index):
    line_cells_on = set()
    line_cells_off = set()
    for i, bit in enumerate(domains[is_col][index][0]):
        if bit == 1:
            line_cells_on.add(i)
        elif bit == 0:
            line_cells_off.add(i)

    for example_solution in domains[is_col][index][1:]:
        for i, bit in enumerate(example_solution):
            if bit == 1:
                try:
                    line_cells_off.remove(i)
                except KeyError:
                    pass
            elif bit == 0:
                try:
                    line_cells_on.remove(i)
                except KeyError:
                    pass
    return line_cells_on, line_cells_off


def get_all_line_uncertain_indexes(domains, is_col, index):
    uncertain_line_cells = set()
    line_cells_on = set()
    line_cells_off = set()
    for i, bit in enumerate(domains[is_col][index][0]):
        uncertain_line_cells.add(i)
        if bit == 1:
            line_cells_on.add(i)
        elif bit == 0:
            line_cells_off.add(i)

    for example_solution in domains[is_col][index][1:]:
        for i, bit in enumerate(example_solution):
            if bit == 1:
                try:
                    line_cells_off.remove(i)
                except KeyError:
                    pass
            elif bit == 0:
                try:
                    line_cells_on.remove(i)
                except KeyError:
                    pass

    uncertain_line_cells.difference_update(line_cells_on)
    uncertain_line_cells.difference_update(line_cells_off)
    return uncertain_line_cells
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
    nonogram = []
    for solutions in domains[0]:
        nonogram.append(solutions[0])
    return nonogram
# endregion


# region Domain
def generate_initial_domains(row_len: int, col_len: int, row_descriptions: List[List[int]], column_descriptions) \
        -> Tuple[List[List[List[int]]], List[List[List[int]]]]:
    row_domains = []
    column_domains = []
    for blocks in row_descriptions:
        row_domains.append(get_all_possible_lines(row_len, len(blocks), blocks))
    for blocks in column_descriptions:
        column_domains.append(get_all_possible_lines(col_len, len(blocks), blocks))
    return row_domains, column_domains


def get_all_possible_lines(line_len: int, blocks_number: int, blocks_lengths: List[int]) -> List[List[int]]:
    def is_correct_block_combination(blocks_start_ids: Tuple[int, ...]) -> bool:
        for i, block_start_id in enumerate(blocks_start_ids):
            is_block_out_of_line = block_start_id + blocks_lengths[i] > line_len
            if is_block_out_of_line:
                return False
            if i + 1 < blocks_number:
                is_block_overlapping_another = block_start_id + blocks_lengths[i] + 1 > blocks_start_ids[i + 1]
                if is_block_overlapping_another:
                    return False
        return True

    def generate_line(blocks_start_ids: Tuple[int, ...]) -> List[int]:
        new_line = [0] * line_len
        for i, block_start_id in enumerate(blocks_start_ids):
            for j in range(blocks_lengths[i]):
                new_line[block_start_id + j] = 1
        return new_line

    all_combinations = itertools.combinations([block_start for block_start in range(line_len)], blocks_number)
    possible_combinations = filter(is_correct_block_combination, all_combinations)
    generated_lines = list(map(generate_line, possible_combinations))
    return generated_lines


# endregion


def main():
    with open("zad_input.txt", 'r') as file:
        height, width = map(int, file.readline().split())
        rows_descriptions = [list(map(int, file.readline().strip().split())) for _ in range(height)]
        columns_descriptions = [list(map(int, file.readline().strip().split())) for _ in range(width)]

    result = solve(rows_descriptions, columns_descriptions, height, width)

    with open("zad_output.txt", "w", encoding='utf-8') as output_file:
        for line in result:
            new_line = ""
            for i in range(len(line)):
                new_line += ("#" if line[i] else ".")

            output_file.write(new_line + "\n")


if __name__ == "__main__":
    main()
