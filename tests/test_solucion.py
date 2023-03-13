archivo = "../instancias/4/big_1000.in"
f = open(archivo)
solucion = open("../instancias/4/big_1000.out")
cant_solucion = int(solucion.readline())
solucion = list(map(lambda h: int(h), solucion.readline().split(" ")))

intervalos_solucion = []
intervalos = []
cant = int(f.readline())
text = f.readlines()

for x in range(cant):
    splited = text[x].split(" ")
    intervalos.append([int(splited[0]), int(splited[1])])


def inter(i, j):
    return i[0] < j[0] < i[1] < j[1] or j[0] < i[0] < j[1] < i[1] or i[0] < j[0] < j[1] < i[1] or j[0] < i[0] < i[1] < \
           j[1]


counter = 0
for index, intervalo in enumerate(intervalos):
    if index not in solucion:
        found = False
        for s in solucion:
            if inter(intervalo, intervalos[s]):
                found = True
        if not found:
            print(str(index) + " no tiene interseccion")

print("fin\n")

