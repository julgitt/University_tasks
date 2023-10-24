from itertools import permutations

def solve_cryptarithmetic(text):
    word1 = text[0]
    word2 = text[1]
    result = text[2]
    operator = text[3]
    unique_letters = list(set("".join(text[:-1])))
    
    for perm in permutations("1234567890", len(unique_letters)):
        
        mapping = dict(zip(unique_letters, perm))
        
        word1_in_number = int(''.join(mapping[letter] for letter in word1))
        word2_in_number = int(''.join(mapping[letter] for letter in word2))
      
        result_in_number = int(''.join(mapping[letter] for letter in result))
        
        if(operator == '+' and word1_in_number + word2_in_number == result_in_number):
            yield mapping
        if(operator == '-' and word1_in_number - word2_in_number == result_in_number):
            yield mapping
        if(operator == '*' and word1_in_number * word2_in_number == result_in_number):
            yield mapping
        if(operator == '/' and word1_in_number / word2_in_number == result_in_number):
            yield mapping
        

def find_all_solutions(input):
    text = input.split()
    for solution in solve_cryptarithmetic(text):
        yield solution

# Przykład użycia:
input = "KIOTO OSAKA TOKIO +"
print(input)
for solution in find_all_solutions(input):
    print(solution)

input = "K O O +"
print(input)
for solution in find_all_solutions(input):
    print(solution)