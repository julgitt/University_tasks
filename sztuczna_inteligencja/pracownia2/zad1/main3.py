import random
import itertools


# region Opt Dist
def opt_dist(init_line, blocks_lengths):

    def find_minimal_inversions(generated_line):
        min_inversion = 0
        for i, cell in enumerate(generated_line):
            min_inversion += bool(cell) ^ bool(init_line[i])
        return min_inversion

    blocks_number = len(blocks_lengths)

    possible_lines = get_all_possible_lines(init_line, blocks_number, blocks_lengths)
    inversions = list(map(find_minimal_inversions, possible_lines))
    minimal_inversion_number = min(inversions)

    best_lines = []
    for idx, line in enumerate(possible_lines):
        if inversions[idx] == minimal_inversion_number:
            best_lines.append(line)

    return random.choice(best_lines)


def get_all_possible_lines(init_line, blocks_number, blocks_lengths):

    def is_correct_block_combination(blocks_start_ids):
        for i, block_start_id in enumerate(blocks_start_ids):
            is_block_out_of_line = block_start_id + blocks_lengths[i] > len(init_line)
            if is_block_out_of_line:
                return False
            if i + 1 < blocks_number:
                is_block_overlapping_another = block_start_id + blocks_lengths[i] + 1 > blocks_start_ids[i + 1]
                if is_block_overlapping_another:
                    return False
        return True

    def generate_line(blocks_start_ids):
        new_line = [0] * len(init_line)
        for i, block_start_id in enumerate(blocks_start_ids):
            for j in range(blocks_lengths[i]):
                new_line[block_start_id + j] = 1
        return new_line

    all_combinations = itertools.combinations([block_start for block_start in range(len(init_line))], blocks_number)
    possible_combinations = filter(is_correct_block_combination, all_combinations)
    generated_lines = list(map(generate_line, possible_combinations))
    return generated_lines
# endregion


# region Check if Solved
def is_line_solved(line, blocks_lengths):
    line_str = '0' + ''.join(map(str, line)) + '0'
    blocks = ['0' + '1' * length + '0' for length in blocks_lengths]
    for i, block in enumerate(blocks):
        found_id = line_str.find(block)
        if found_id == -1:
            return False
        prefix_length = found_id + blocks_lengths[i]
        line_str = line_str[prefix_length:]
    is_number_of_blocks_correct = sum(map(int, blocks_lengths)) == sum(map(int, line))
    if not is_number_of_blocks_correct:
        return False
    return True


def is_nonogram_solved(nonogram, rows_descriptions, cols_descriptions):
    for i in range(0, len(rows_descriptions)):
        if not is_line_solved(nonogram[i], rows_descriptions[i]):
            return False
    transposed_nonogram = transpose_nonogram(nonogram)
    for i in range(0, len(cols_descriptions)):
        if not is_line_solved(transposed_nonogram[i], cols_descriptions[i]):
            return False
    return True


# endregion


# region Solve
def solve(rows_descriptions, cols_descriptions, height, width, max_iterations):
    nonogram = generate_nonogram(width, height)

    current_iteration = 0
    is_transposed = False
    while not is_nonogram_solved(nonogram, rows_descriptions, cols_descriptions):
        if current_iteration > max_iterations:
            current_iteration = 0
            nonogram = generate_nonogram(width, height)

        line = get_random_line(nonogram, rows_descriptions)
        new_line = opt_dist(line, rows_descriptions[nonogram.index(line)])
        nonogram[nonogram.index(line)] = new_line

        if random.randint(0, 100) >= 50:
            is_transposed = not is_transposed
            nonogram = transpose_nonogram(nonogram)
            cols_descriptions, rows_descriptions = rows_descriptions, cols_descriptions

        current_iteration += 1

    if is_transposed:
        nonogram = transpose_nonogram(nonogram)
    return nonogram
# endregion


# region Nonogram Operations
def generate_nonogram(width, height):
    return [[0 for _ in range(width)] for _ in range(height)]


def transpose_nonogram(nonogram):
    return [[nonogram[row_id][col_id] for row_id in range(len(nonogram))] for col_id in range(len(nonogram[0]))]


def get_random_line(nonogram, rows_descriptions):
    line = random.choice(nonogram)
    iterations = 0
    while is_line_solved(line, rows_descriptions[nonogram.index(line)]) and iterations <= 100:
        iterations += 1
        line = random.choice(nonogram)
    return line


# endregion


def main():
    iterations = 500

    with open("zad_input.txt", 'r') as file:
        height, width = map(int, file.readline().split())
        rows_descriptions = [list(map(int, file.readline().strip().split())) for _ in range(height)]
        columns_descriptions = [list(map(int, file.readline().strip().split())) for _ in range(width)]

    result = solve(rows_descriptions, columns_descriptions, height, width, iterations * width * height)

    with open("zad_output.txt", "w", encoding='utf-8') as output_file:
        for line in result:
            new_line = ""
            for i in range(len(line)):
                if line[i]:
                    new_line += ("#" if line[i] else ".")

            output_file.write(new_line + "\n")


if __name__ == "__main__":
    main()
