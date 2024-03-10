import gzip

word_exist_cache = {}
word_not_exist_cache = {}

MAX_LEN = 0
WORDS = set()
INPUT = []


# region load inputs from files
def load_input_from_file():
    with open("zad2_input.txt", 'r', encoding='utf-8') as file:
        for line in file:
            text = line.strip()
            INPUT.append(text)


def load_words_from_file():
    global MAX_LEN
    with gzip.open("zad2_words.txt.gz", 'rt', encoding='utf-8') as file:
        for line in file:
            word = line.strip()
            WORDS.add(word)
            MAX_LEN = max(MAX_LEN, len(word))


# endregion

# region solution_logic
def find_words(text):
    global MAX_LEN
    memo = {}

    def dp(start):
        if start in memo:
            return memo[start]

        if start == len(text):
            return ""

        best_peak = ""
        max_sum = 0
        for end in range(start + 1, min(start + MAX_LEN + 1, len(text) + 1)):
            word = text[start:end]
            if word_exists(word):
                rest = dp(end)
                squared_sum = sum_of_squared_word_lengths(word + " " + rest)
                if squared_sum > max_sum:
                    max_sum = squared_sum
                    best_peak = word + " " + rest

        memo[start] = best_peak
        return best_peak

    return dp(0)


def word_exists(word):
    if word in word_not_exist_cache:
        return False

    if word in word_exist_cache or word in WORDS:
        word_exist_cache[word] = True
        return True

    word_not_exist_cache[word] = True
    return False


def sum_of_squared_word_lengths(text):
    return sum(len(word) ** 2 for word in text.split())


# endregion

# region main
def main():
    load_words_from_file()
    load_input_from_file()

    with open("zad2_output.txt", "w", encoding='utf-8') as output_file:
        for text in INPUT:
            final_text = find_words(text)
            output_file.write(final_text + '\n')


if __name__ == "__main__":
    main()
# endregion
