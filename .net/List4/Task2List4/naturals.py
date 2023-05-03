n = 350
filename = "Task2List4/text.txt"

with open(filename, "w") as f:
    for i in range(1, n+1):
        f.write(str(i) + "\n")