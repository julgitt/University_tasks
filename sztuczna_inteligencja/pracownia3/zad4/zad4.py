
def B(i, j):
    return 'B_%d_%d' % (i, j)


def domains(Vs):
    for q in Vs:
        writeln(q + ' in 0..1,')


def check_rows(rows, cols_num):
    result = []
    for i, row in enumerate(rows):
        all_vals_in_row = [B(i, j) for j in range(cols_num)]
        writeln('sum([' + ', '.join(all_vals_in_row) + '], #=, ' + str(row) + '), ')
    return result


def check_cols(cols, rows_num):
    result = []
    for j, col in enumerate(cols):
        all_vals_in_col = [B(i, j) for i in range(rows_num)]
        writeln('sum([' + ', '.join(all_vals_in_col) + '], #=, ' + str(col) + '), ')
    return result


# A + 2B + 3C != 2
# Jeżeli środkowy piksel jest ustawiony, to wówczas przynajmniej 1 z
# otaczających go jest jedynką.
def good_three_cells_in_rows(cols_num, rows_num):
    for j in range(cols_num):
        for i in range(rows_num - 2):
            a = B(i, j)
            b = B(i + 1, j)
            c = B(i + 2, j)
            writeln(b + ' #= 1 #==> ' + a + ' + ' + c + '#> 1, ')


def good_three_cells_in_cols(cols_num, rows_num):
    for j in range(cols_num - 2):
        for i in range(rows_num):
            a = B(i, j)
            b = B(i, j + 1)
            c = B(i, j + 2)
            writeln(b + ' #= 1 #==> ' + a + ' + ' + c + '#> 1, ')


# B × (A + C) != 2
def rectangle(cols_num, rows_num):
    for j in range(cols_num - 1):
        for i in range(rows_num - 1):
            a = B(i, j)
            b = B(i, j + 1)
            c = B(i + 1, j)
            d = B(i + 1, j + 1)
            writeln(a + ' + ' + d + ' #= 2 #<==> ' + b + ' + ' + c + ' #= 2, ')


def print_constraints(Cs, indent, d):
    position = indent
    print(indent * ' ', end='')
    for c in Cs:
        print(c + ',', end=' ')
        position += len(c)
        if position > d:
            position = indent
            print()
            print(indent * ' ', end='')


def storms(rows, cols, triples):
    writeln(':- use_module(library(clpfd)).')
    
    R = len(rows)
    C = len(cols)
    
    bs = [B(i, j) for i in range(R) for j in range(C)]
    
    writeln('solve([' + ', '.join(bs) + ']) :- ')
    
    #TODO: add some constraints

    domains(bs)
    check_rows(rows, C)
    check_cols(cols, R)
    good_three_cells_in_cols(C, R)
    good_three_cells_in_rows(C, R)
    rectangle(C, R)

    for i, j, val in triples:
        output.write('%s #= %d, ' % (B(i, j), val))

    writeln('    labeling([ff], [' + ', '.join(bs) + ']).')
    writeln('')
    writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")


def writeln(s):
    output.write(s + '\n')


txt = open('zad_input.txt').readlines()
output = open('zad_output.txt', 'w')

rows = list(map(int, txt[0].split()))
cols = list(map(int, txt[1].split()))
triples = []

for i in range(2, len(txt)):
    if txt[i].strip():
        triples.append(map(int, txt[i].split()))

storms(rows, cols, triples)            
        

