import gzip
import re

from random_word_reconstructor import RandomReconstructor
from word_reconstructor import Reconstructor

NOT_ALLOWED_CHARS = re.compile(r'[\W\s]+')
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


def count_correct_words(original_text, text):
    correct_words = 0
    j = 0
    i = 0
    incorrect_word = False
    while i < len(original_text):
        t = original_text[i]
        w = text[j]
        if original_text[i] != text[j] == " ":
            incorrect_word = True
            j += 1
            continue
        elif original_text[i] == " " != text[j]:
            incorrect_word = True
            i += 1
            continue
        elif text[j] == " " and not incorrect_word:
            correct_words += 1
        elif text[j] == " ":
            incorrect_word = False
        i += 1
        j += 1

    if not incorrect_word and text[j - 1] != " ":
        correct_words += 1
    return correct_words


def print_stats(result1, result2, all_words):
    print(f"Algorithm maximizing word length:\n"
          f"correct_words: {result1} / {all_words}, accuracy: {result1 * 100 / all_words:.2f}%")
    print(f"Algorithm randomly picking word size:\n"
          f"correct_words: {result2} / {all_words}, accuracy: {result2 * 100 / all_words:.2f}%")


def main():
    words, max_len = load_words_from_file()
    lines = load_input_from_file(INPUT_FILENAME)
    original_lines = load_input_from_file(ORIGINAL_FILENAME)

    all_words_counter = 0
    correct_words_counter = 0
    correct_random_words_counter = 0

    with open("reconstructed.txt", "w", encoding='utf-8') as reconstructed, \
            open("randomly_reconstructed.txt", "w", encoding='utf-8') as randomly_reconstructed:
        for i in range(len(lines)):
            line = lines[i]
            original_line = re.sub(NOT_ALLOWED_CHARS, " ", original_lines[i].lower())

            all_words_counter += len(original_line.split())

            random_reconstructor = RandomReconstructor(line, max_len, words)
            reconstructor = Reconstructor(line, max_len, words)
            if i == 450:
                print("")
            randomly_reconstructed_text = random_reconstructor.find_words()
            reconstructed_text = reconstructor.find_words()

            reconstructed.write(reconstructed_text + '\n')
            randomly_reconstructed.write(randomly_reconstructed_text + '\n')

            correct_words_counter += count_correct_words(original_line, reconstructed_text)
            correct_random_words_counter += count_correct_words(original_line, randomly_reconstructed_text)

    print_stats(correct_words_counter, correct_random_words_counter, all_words_counter)


if __name__ == "__main__":
    main()
