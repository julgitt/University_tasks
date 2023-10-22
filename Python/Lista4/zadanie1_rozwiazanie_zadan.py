from itertools import permutations

def solve_cryptarithmetic(text):
    words = text[:-1]
    result = text[-1]
    unique_letters = list(set("".join(text)))
    
    for perm in permutations("1234567890", len(unique_letters)):
        #if perm[unique_letters.index(words[0][0])] == '0':
        #    continue
        
        mapping = dict(zip(unique_letters, perm))
        
        words_in_numbers = [int(''.join(mapping[letter] for letter in word)) for word in words]
        result_in_number = int(''.join(mapping[letter] for letter in result))
        
        if sum(words_in_numbers) == result_in_number:
            yield mapping

def solving_task(input):
    puzzle = input.split()
    for solution in solve_cryptarithmetic(puzzle):
        yield solution

# Przykład użycia:
input = "KIOTO OSAKA TOKIO"
for solution in solving_task(input):
    print(solution)

input = "K O O"
for solution in solving_task(input):
    print(solution)