from matplotlib import pyplot as plt
import random
import pylab

INPUT_FILEPATH = '../data/output.txt'

def random_color():
    return (random.random(), random.random(), random.random())

file = open(INPUT_FILEPATH, 'r')
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []
data = []
for line in file:
    if not line.strip():
        data.append((xs, ys))
        xs, ys = [], []
    else:
        x, y = map(float, line.split())
        xs.append(x)
        ys.append(y)

for fig in data:
    plt.plot(fig[0], fig[1], color=random_color(), marker='o')
plt.show()
