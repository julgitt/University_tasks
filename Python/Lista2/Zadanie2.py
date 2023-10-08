import time
import sys
sys.setrecursionlimit(1500)

def sudan(n, x, y):
    if n == 0:
        return x + y
    if y == 0 and x >= 0:
        return x
    return sudan(n - 1, sudan(n, x, y - 1), sudan(n, x, y - 1) + y)

def memoize(func):
    def memoized_func(*args):
        if args in memoized_func.cache:
            return memoized_func.cache[args]
        result = func(*args)
        memoized_func.cache[args] = result
        return result
    memoized_func.cache = {}
    return memoized_func

@memoize
def m_sudan(n, x, y):
    if n == 0:
        return x + y
    if y == 0 and x >= 0:
        return x
    return m_sudan(n - 1, m_sudan(n, x, y - 1), m_sudan(n, x, y - 1) + y)

start = time.time()

# przy większych liczbach trwa długo
sudan(2, 1, 2)

end = time.time()

print("%3f" %  (end - start))

start = time.time()

# przy większych liczbach ograniczeniem jest przekroczenie głęgokości rekrencji
m_sudan(2, 3, 2)

end = time.time()
print("%3f" %  (end - start))
