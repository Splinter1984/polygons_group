from matplotlib import pyplot as plt
from matplotlib.ticker import MultipleLocator
from matplotlib.backend_bases import MouseButton
#   from matplotlib.widgets import Button
#   import random
#   import os

POINT_RADIUS = 0.5
OUTPUT_FILEPATH = '../data/input.txt'
DRAW_COLOR = 'black'

class LineBuilder:
    def __init__(self, line, plt, file, coll=0.1):
        self.plt = plt
        self.coll = coll
        self.line = line
        self.file = file
        self.xs = list(line.get_xdata())
        self.ys = list(line.get_ydata())
        self.cid = line.figure.canvas.mpl_connect('button_press_event', self)

    def __call__(self, event):
        print ('click ', event)
        coll_x = round(event.xdata, 0)
        coll_y = round(event.ydata, 0)
        if event.button is MouseButton.RIGHT:
            for x, y in zip(self.xs, self.ys):
                if (x-event.xdata)*(x-event.xdata) + (y-event.ydata)*(y-event.ydata) <= self.coll*self.coll:
                    coll_x = x
                    coll_y = y
            self.xs.append(coll_x)
            self.ys.append(coll_y)
            self.line.set_data(self.xs, self.ys)

        if event.button is MouseButton.LEFT:
            line, = plt.plot([coll_x], [coll_y], c=DRAW_COLOR, marker='o')
            self.xs = [coll_x]
            self.ys = [coll_y]
            self.line = line
            self.file.write('\n')

        self.file.write(str(coll_x) + ' ' + str(coll_y) + '\n')
        self.line.figure.canvas.draw()


file = open(OUTPUT_FILEPATH, 'w')
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
plt.title("use Mouse RIGHT for build line/ LEFT for set new point")
plt.xlim(0, 10)
plt.ylim(0, 10)
ax.xaxis.set_major_locator(MultipleLocator(1))
ax.yaxis.set_major_locator(MultipleLocator(1))
plt.grid(True)
#file.write(str(5) + ' ' + str(5) + '\n')
line, = plt.plot([], [], c=DRAW_COLOR, marker = 'o')
linebuilder = LineBuilder(line, plt, file, POINT_RADIUS)

plt.show()