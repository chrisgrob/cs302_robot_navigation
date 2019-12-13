import numpy as np
import matplotlib.pyplot as plt

data = np.array((1000, 1000))

file = open('probabilities.txt')

for row, line in enumerate(file):
    probabilities = line.strip().split()

    for col in range(0, 1000):
        data[row][col] = float(probabilities[col])

plt.imshow(data)
