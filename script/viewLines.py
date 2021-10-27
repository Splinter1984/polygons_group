from matplotlib import pyplot as plt
import random
import pylab

INPUT_FILEPATH = '../data/output.txt'

def random_color():
    return (random.random(), random.random(), random.random())

file = open(INPUT_FILEPATH, 'r')
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
layer = 0
xs = []
ys = []
data = []
for line in file:
    if not line.strip():
        data.append(((xs, ys), layer))
        xs, ys = [], []
    else:
        if "layer" in line:
            layer = int(line.split(':')[1])
        else:
            x, y = map(int, line.split())
            xs.append(x)
            ys.append(y)
if data[0][1] % 2 == 0:
    color_pattern = 0
else:
    color_pattern = 1

for fig in data:
    plt.plot(fig[0][0], fig[0][1], color='gray', marker='o')
    if (fig[1] % 2 != 0):
        plt.fill(fig[0][0], fig[0][1], color='gray', alpha=0.7)
    else:
        plt.fill(fig[0][0], fig[0][1], color='white')
plt.show()
