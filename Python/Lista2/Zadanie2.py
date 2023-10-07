import time
import sys
sys.setrecursionlimit(5000)

def sudan(n, x, y):
    if n == 0:
        return x + y
    if y == 0 and x >= 0:
        return x
    return sudan(n - 1, sudan(n, x, y - 1), sudan(n, x, y - 1) + y)


sudan_cache = {}


def m_sudan(n, x, y):
    if (n, x, y) in sudan_cache:
        return sudan_cache[(n, x, y)]
    if n == 0:
        result = x + y
    elif y == 0 and x >= 0:
        result = x
    else:
        result = m_sudan(n - 1, m_sudan(n, x, y-1), m_sudan(n, x, y-1) + y)
    sudan_cache[(n, x, y)] = result
    return result


'''def memoize(func):
    def memoized_func(*args):
        if args in memoized_func.cache:
            return memoized_func.cache [args]
        result = func(*args)
        memoized_func.cache[args] = result
        return result
    memoized_func.cache = dict()
    return memoized_func'''

start = time.time()

sudan(2, 2, 1)

end = time.time()

print(end - start)

start = time.time()
m_sudan(2, 3, 2)

end = time.time()
print(end - start)
