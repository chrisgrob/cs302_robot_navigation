import numpy as np
import matplotlib.pyplot as plt

data = np.zeros((1000, 1000), float)

file = open('probabilities.txt')

for row, line in enumerate(file):
    probabilities = line.strip().split()

    for col in range(0, 1000):
        data[row][col] = float(probabilities[col])

plt.matshow(data)
plt.show()
