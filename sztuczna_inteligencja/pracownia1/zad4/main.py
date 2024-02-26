def opt_dist(bits, D):
    min_operations = float('inf')
    for i in range(len(bits) - D + 1):
        operations = bits.count('1', 0, i) + bits.count('0', i, i + D) + bits.count('1', D + i, len(bits))
        min_operations = min(min_operations, operations)
    
    return min_operations

print(opt_dist("0010001000", 5))  # Output: 3   
print(opt_dist("0010001000", 4))  # Output: 4
print(opt_dist("0010001000", 3))  # Output: 3
print(opt_dist("0010001000", 2))  # Output: 2
print(opt_dist("0010001000", 1))  # Output: 1
print(opt_dist("0010001000", 0))  # Output: 2
