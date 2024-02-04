from timeit import default_timer

def is_prime_imperative(n):
    if n <= 1:
        return False
 
    for i in range (2, n // 2 + 1):
        if n % i == 0:
            return False
 
    return True

def is_prime_comprehension(n):
    return n > 1 and all(n % i != 0 for i in range(2, n // 2 + 1))

def is_prime_functional(n):
    return n > 1 and sum(1 for i in range(2, n // 2 + 1) if n % i == 0) == 0

def imperative(n):
    res = []
    for i in range(1, n + 1):
        if is_prime_imperative(i):
            res.append(i)
    return res


def comprehension(n):
    return [i for i in range(1, n + 1) if is_prime_comprehension(i)]


def functional(n):
    return list(filter(is_prime_functional, range(1, n+1)))


print("n".ljust(20) + "imperative".ljust(20) + "comprehension".ljust(20) + "functional".ljust(20))
i = 50
imp = 0
com = 0
fun = 0
while i <= 90:
    line = str(i).ljust(20)

    for  j in range (10000):
        start = default_timer()
        imperative(i)
        end = default_timer()
        imp += end - start
    
    line += str(round(imp / 10000, 4)).ljust(20)

    for  j in range (10000):
        start = default_timer()
        comprehension(i)
        end = default_timer()
        com +=  end - start
    
    line += str(round(com / 10000, 4)).ljust(20)
   
    for  j in range (10000):
        start = default_timer()
        functional(i)
        end = default_timer()
        fun +=  end - start
    
    line += str(round(fun / 10000, 4)).ljust(20)

    print(line)
    i += 1

print(imperative(19))
print(comprehension(19))
print(functional(19))
