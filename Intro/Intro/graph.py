import csv
import numpy as np
import matplotlib.pyplot as plt

x = []
y = []

with open('outData.csv') as File:
	plots = csv.reader(File, delimiter = ',')
	for row in plots:
		x.append(int(row[0]))
		y.append(float(row[3]))

plt.xlabel('K value')
plt.ylabel('Run Times in 1e-5 seconds')
plt.title('Run times of y function with different K values and randomly ordered lists')
plt.show()