import math
import matplotlib.pyplot as plt
import numpy as np

def frange(Start, Stop, Step):
    x = Start
    if (Start < Stop) and (Step > 0):
        while x <= Stop:
            yield x
            x += Step
    elif (Start > Stop) and (Step < 0):
        while x >= Stop:
            yield x
            x += Step
    else:
        raise ValueError("Loop won't stop")

def H2(e):
    """
    Binary entropy function
    """

    h2 = (-e * math.log(e, 2)) - ((1 - e) * math.log((1 - e), 2))

    return h2

def QuickTriPlot(Data):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")
    ax = Axes3D(fig)
    ax.plot_trisurf(*Data.T, cmap=cm.rainbow)
    plt.show()