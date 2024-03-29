INPUT = []

#region load input from a file
def load_input_from_file():
    with open("zad4_input.txt", 'r', encoding='utf-8') as file:
        for line in file:
            input = line.split(' ')
            INPUT.append((input[0], int(input[1])))
#endregion            

#region solution
def opt_dist(bits, block_size):
    min_operations = float('inf')
    for i in range(len(bits) - block_size + 1):
        operations = bits.count('1', 0, i) + bits.count('0', i, i + block_size) + bits.count('1', block_size + i, len(bits))
        min_operations = min(min_operations, operations)
    
    return min_operations
#endregion

#region main
def main():
    load_input_from_file()
    
    with open("zad4_output.txt", "w", encoding='utf-8') as output_file:
        for line, num in INPUT:
            result = opt_dist(line, num)
            output_file.write(str(result) + '\n')


if __name__ == "__main__":
    main()
#endregion

#region example usage
'''    
print(opt_dist("0010001000", 5))  # Output: 3   
print(opt_dist("0010001000", 4))  # Output: 4
print(opt_dist("0010001000", 3))  # Output: 3
print(opt_dist("0010001000", 2))  # Output: 2
print(opt_dist("0010001000", 1))  # Output: 1
print(opt_dist("0010001000", 0))  # Output: 2
'''
#endregion
