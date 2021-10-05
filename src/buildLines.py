from matplotlib import pyplot as plt
from matplotlib.backend_bases import MouseButton
from matplotlib.widgets import Button
import random
import os

fig_data = []

class LineBuilder:
    def __init__(self, line, plt, file, coll=0.01):
        self.plt = plt
        self.coll = coll
        self.line = line
        self.file = file
        self.xs = list(line.get_xdata())
        self.ys = list(line.get_ydata())
        self.cid = line.figure.canvas.mpl_connect('button_press_event', self)

    def __call__(self, event):
        print ('click ', event)
        coll_x = round(event.xdata, 2)
        coll_y = round(event.ydata, 2)
        if event.button is MouseButton.RIGHT:
            for x, y in zip(self.xs, self.ys):
                if (x-event.xdata)*(x-event.xdata) + (y-event.ydata)*(y-event.ydata) <= self.coll*self.coll:
                    coll_x = x
                    coll_y = y
            self.xs.append(coll_x)
            self.ys.append(coll_y)
            self.line.set_data(self.xs, self.ys)

        if event.button is MouseButton.LEFT:
            color = color_gen()
            fig_data.append(list((self.xs, self.ys)))
            self.file.write("\n")
            line, = plt.plot([coll_x], [coll_y], c=color, marker='o')
            self.xs = [coll_x]
            self.ys = [coll_y]
            self.line = line

        self.file.write(str(coll_x) + ' ' + str(coll_y) + '\n')
        self.line.figure.canvas.draw()


def color_gen():
    return (random.random(), random.random(), random.random())

file = open('data/fig.txt', 'w')
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
plt.xlim(0, 10)
plt.ylim(0, 10)
file.write(str(5) + ' ' + str(5) + '\n')
line, = plt.plot([5], [5], c=color_gen(), marker = 'o')  # empty line
linebuilder = LineBuilder(line, plt, file,  0.5)

plt.show()