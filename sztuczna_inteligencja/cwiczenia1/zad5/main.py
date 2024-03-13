blotkarz_total = 376992
figurant_total = 4368
blotkarz = [20, 288, 1728, 484, 5100, 16128, 36288, 193536]
figurant = [0, 48, 288, 0, 0, 768, 1728, 1536]

blotkarz_probability = [x / blotkarz_total for x in blotkarz]
figurant_probability = [x / figurant_total for x in figurant]

res: float = 0.0
for i in range(7):
    for j in range(i + 1, 8):
        res += blotkarz_probability[i] * figurant_probability[j]

print(f'Blotkarz probability of winning: {res *  100:.2f}%')
