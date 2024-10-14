x = [0, 1, 2]
y = [True, False, False]

x = [o for o, b in zip(x, y) if b]
print(x)