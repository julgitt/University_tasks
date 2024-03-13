import gzip
import re

from random_word_reconstructor import RandomReconstructor
from word_reconstructor import Reconstructor

NOT_ALLOWED_CHARS = re.compile(r'[\W\s]+')
MULTIPLE_SPACES = re.compile(r'\s+')
ORIGINAL_FILENAME = "pan-tadeusz.txt"
INPUT_FILENAME = "pan_tadeusz_bez_spacji.txt"
WORDS_FILENAME = "words.txt.gz"


def load_input_from_file(filename):
    result = []
    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            text = line.strip()
            if text:
                result.append(text)
    return result


def load_words_from_file():
    words = set()
    max_len = 0
    with gzip.open(WORDS_FILENAME, 'rt', encoding='utf-8') as file:
        for line in file:
            word = line.strip()
            words.add(word)
            max_len = max(max_len, len(word))
    return words, max_len


def check_if_correct_line(original_text, text):
    return 1 if original_text == text else 0


def print_stats(result1, result2, all_lines):
    print(f"Algorithm maximizing word length:\n"
          f"correct_words: {result1} / {all_lines}, accuracy: {result1 * 100 / all_lines:.2f}%")
    print(f"Algorithm randomly picking word size:\n"
          f"correct_words: {result2} / {all_lines}, accuracy: {result2 * 100 / all_lines:.2f}%")


def format_text(text):
    processed_string = re.sub(NOT_ALLOWED_CHARS, " ", text.lower())
    processed_string = re.sub(MULTIPLE_SPACES, ' ', processed_string)
    if processed_string[-1] == ' ':
        processed_string = processed_string[:-1]
    if processed_string[0] == ' ':
        processed_string = processed_string[1:]
    return re.sub(MULTIPLE_SPACES, ' ', processed_string)


def main():
    words, max_len = load_words_from_file()
    lines = load_input_from_file(INPUT_FILENAME)
    original_lines = load_input_from_file(ORIGINAL_FILENAME)

    correct_lines_counter = 0
    correct_random_lines_counter = 0

    with open("reconstructed.txt", "w", encoding='utf-8') as reconstructed, \
            open("randomly_reconstructed.txt", "w", encoding='utf-8') as randomly_reconstructed:
        for i in range(len(lines)):
            line = lines[i]
            original_line = format_text(original_lines[i])

            random_reconstructor = RandomReconstructor(line, max_len, words)
            reconstructor = Reconstructor(line, max_len, words)

            randomly_reconstructed_text = random_reconstructor.find_words()
            reconstructed_text = reconstructor.find_words()

            reconstructed.write(reconstructed_text + '\n')
            randomly_reconstructed.write(randomly_reconstructed_text + '\n')

            if check_if_correct_line(original_line, reconstructed_text) == 0:
                print("")
            correct_lines_counter += check_if_correct_line(original_line, reconstructed_text)
            correct_random_lines_counter += check_if_correct_line(original_line, randomly_reconstructed_text)

    print_stats(correct_lines_counter, correct_random_lines_counter, len(lines))


if __name__ == "__main__":
    main()
