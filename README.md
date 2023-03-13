# algo3tp2


## Compilacion rapida
Para compilar corra los siguientes comandos, estos generan los 5 ejecutables en la subcarpeta instancias/ejX

```bash
cmake .
make
```
Nos movemos a la carpeta intancias y a la subcarpeta correspondiente y ahi podemos hacer
```bash
./ejX < path/to/test/file > path/to/output/file
```
Donde X es el numero de ejericio.

De querer usar docker hacer lo siguiente:
```bash
docker-compose up -d --build
docker ps #buscamos la id del contenedor
docker exec -ti <container-id> bash
cd data/instancias #lugar por defecto de los binarios
```

## Mas detalles


Una opción alternativa para compilar los archivos es colocar en la consola:
```bash
g++ -no-pie -c -m64 -O3 ej1.cpp -o ej1f.o && g++ -no-pie -O3 -o ./ej1 -m64 ej1f.o
g++ -no-pie -c -m64 -O3 ej2.cpp -o ej2f.o && g++ -no-pie -O3 -o ./ej2 -m64 ej2f.o
g++-11 -no-pie -c -m64 -O3 ej3.cpp -o ej3f.o && g++11 -no-pie -O3 -o ./ej3 -m64 ej3f.o
g++ -no-pie -c -m64 -O3 ej4.cpp -o ej4f.o && g++ -no-pie -O3 -o ./ej4 -m64 ej4f.o
```

En caso de que esta opción siga sin funcionar:
```bash
g++ -c ej1.cpp && g++ -o ej1.exe ej1.o
g++ -c ej2.cpp && g++ -o ej2.exe ej2.o
g++ -c ej3.cpp && g++ -o ej3.exe ej3.o #(Ojo)
g++ -c ej4.cpp && g++ -o ej4.exe ej4.o
```

En particular el ejercicio 3 para compilar necesita una versión de g++ de 11. El resto debería ser posible compilarlo con una versión 7.5 de g++.