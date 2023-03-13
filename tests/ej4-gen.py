import random
import os
from time import sleep
import numpy as np


def gen_one(n, C):
    I = []
    used = [False] * (2 * n)
    for i in range(2 * n):
        if used[i]: continue
        used[i] = True

        while 1:
            j = random.randint(i, min(i + C, 2 * n - 1))
            if not used[j]:
                used[j] = True
                break

        I.append([i, j])
    return I


def gen(n=5, C=99999):
    while 1:
        I = gen_one(n, C)

        # checkeo que sea factible ("conexo")
        c = I[0][1]
        bad = False
        for i in range(1, n):
            if I[i][0] > c:
                bad = True

                # print("REJECTING: ", I)

                break
            c = max(c, I[i][1])

        if not bad:
            return I


N = 20000
C = 2500
# print("N =", N)
# I = gen(N, C)
# print("I =", I)

numbers = []
for x in range(4, 10000):
    N = x
    I = gen(N, C)
    numero = str(N)
    if len(numero) == 1: numero = "0" + numero
    if len(numero) == 2: numero = "0" + numero
    if len(numero) == 3: numero = "0" + numero
    with open(f'pearson/big-{numero}.in', 'w+') as f:
        f.write(f'{N}\n')
        for i in I:
            f.write(f'{i[0]} {i[1]}\n')
