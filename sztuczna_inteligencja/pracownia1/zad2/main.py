
max_len = 0
word_exist_cache = {}
word_not_exist_cache = {}
words = set()

def init_words():
    with open("words.txt", 'r', encoding='utf-8') as file:
        for line in file:
            word = line.strip().replace('\n', '')
            words.add(word)
            max_len = max(max_len, word)


def find_words(text, word_len):
    (max_sum, current_best_peak) = (0, "")
    for i in range(word_len):
        new_text = body(text, i)
        squared_sum = sum_of_squared_word_lengths(new_text)
        if max_sum < squared_sum:
            max_sum = squared_sum
            current_best_peak = new_text
    return current_best_peak
    
def body(text, word_len):
    if word_len == 0:
        return ''
    
    current_word = text[:word_len]
    if word_exists(current_word):
        return current_word + find_words(text[word_len:], max_len)
    return find_words(text, word_len - 1)

    
def sum_of_squared_word_lengths(text):
    words = text.split()
    sum_of_squares = sum(len(word) ** 2 for word in words)
    return sum_of_squares   




def word_exists(word):
    if len(word) > max_len:
        return False
    
    if word in word_exist_cache:
        return word_exist_cache[word]
    
    if word in word_not_exist_cache:
        return False
    
    if word in words:
        word_exist_cache[word] = True
        return True
    
    word_not_exist_cache[word] = True
    return False



init_words()

with open("output.txt", "w", encoding='utf-8') as output_file, \
     open("input.txt", 'r', encoding='utf-8') as file:
    for line in file:
        text = find_words(line.strip().replace('\n', ''), max_len)
        output_file.write(text + '\n')
