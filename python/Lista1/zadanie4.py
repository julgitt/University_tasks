import numpy as np

def pi_approximation(number_of_draws, side_length):
    in_circle = 0

    x = np.random.uniform(0.0, side_length, number_of_draws)
    y = np.random.uniform(0.0, side_length, number_of_draws)

    in_circle = np.sum(circle_equation(x, y, side_length))

    return (in_circle * 4) / number_of_draws


def circle_equation(x, y, r):
    return (x - r)**2 + (y - r)**2 <= r**2 


print(pi_approximation(100000, 1))