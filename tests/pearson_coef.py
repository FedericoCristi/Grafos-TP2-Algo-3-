import numpy as np
import pandas as pd
from subprocess import run

rang = []
f = open("pearson/tiempos.out")
lines = f.readlines()
lines = list(map(lambda l: float(l) * 100, lines))

for x in range(len(lines)):
    rang.append(x*x)

r = np.corrcoef(lines, rang)
#r = np.polyfit(rang, lines, 2)
print(r)
