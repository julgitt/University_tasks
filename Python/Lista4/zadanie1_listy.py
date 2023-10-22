from timeit import default_timer
import math

def is_prime(n):
    if n <= 1:
        return False
 
    for i in range (2, n // 2 + 1):
        if n % i == 0:
            return False
 
    return True


def imperative(n):
    res = []
    for i in range(1, n + 1):
        if is_prime(i):
            res.append(i)
    return res


def comprehension(n):
    return [i for i in range(1, n + 1) if is_prime(i)]


def functional(n):
    return list(filter(is_prime, range(1, n+1)))


print("n    imperative    comprehension    functional")
i = 9000
imp = 0
com = 0
fun = 0
while i <= 9500:
    line = str(i) + ":    "

    start = default_timer()
    imperative(i)
    end = default_timer()
    imp += end - start
    line += str(round(end - start, 4)) + "    "

    start = default_timer()
    comprehension(i)
    end = default_timer()
    com += end - start
    line += str(round(end - start, 4)) + "    "

    start = default_timer()
    functional(i)
    end = default_timer()
    fun += end - start
    line += str(round(end - start, 4))

    print(line)
    i += 1

print(f"mean values:    {imp / 500}    {com / 500}    {fun / 500}")

print(imperative(19))
print(comprehension(19))
print(functional(19))
