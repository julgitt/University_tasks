import math

colors = int(input())
balls = []

for i in range(colors):
    balls.append(int(input()))

result = 1
sum_balls = sum(balls)


for i in range(colors - 1, -1, -1):
    if balls[i] > 1:
        result = (result * math.comb(sum_balls - 1, balls[i] - 1)) % 1000000007
    sum_balls -= balls[i]

print(result);

