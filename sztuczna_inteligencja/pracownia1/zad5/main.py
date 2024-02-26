import random

INPUT = []

image_width = 0
image_height = 0
rows = []
columns = []

#region input
def load_input_from_file():
    global image_width, image_height
    with open("zad5_input.txt", 'r') as file:
        image_width, image_height = map(int, file.readline().split())
        for _ in range(image_width):
            columns.append(int(file.readline()))
        for _ in range(image_height):
            rows.append(int(file.readline()))
#endregion


#region solve_line
def fix_line(bits, D):
    min_operations = float('inf')
    fixed_line = bits
    
    for i in range(len(bits) - D + 1):
        operations = bits.count('#', 0, i) + bits.count('.', i, i + D) + bits.count('#', D + i, len(bits))
        if min_operations > operations: 
            min_operations = operations
            fixed_line = '.' * i + '#' * D + '.' * (len(bits) - D - i)
            
    
    return min_operations, fixed_line
#endregion

def solve():
    while(True):
        image = generate_random_image()
        for _ in range(10):
            operations = 0
            
            for i in range(image_height):
                _, new_line = fix_line(image[i], columns[i])
                image[i] = new_line
            
            rotated_image = rotate_image(image)
            
            for i in range(image_width):
                new_operations, new_line = fix_line(rotated_image[i], rows[i])
                rotated_image[i] = new_line
                operations += new_operations
                
            image = rotate_image(rotated_image)
            if (operations == 0):
                return image
            

def rotate_image(image):
    rotated_image = []
    for i in range(len(image[0])):
        rotated_image.append("".join([line[i] for line in image]))
    return rotated_image

#region random_image_generation
def generate_random_image():
    image = []
    for _ in range(image_height):
        image.append(generate_random_binary_string(image_width))
        
    return image

    
def generate_random_binary_string(length):
    return ''.join(random.choice('.#') for _ in range(length))
#endregion

#region main
def main():
    load_input_from_file()
    
    with open("zad5_output.txt", "w", encoding='utf-8') as output_file:
        for line in solve():
            output_file.write(line + '\n')


if __name__ == "__main__":
    main()
#endregion