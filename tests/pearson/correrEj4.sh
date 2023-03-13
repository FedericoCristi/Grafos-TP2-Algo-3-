#!/bin/bash
for file in ./big-*.in
do
  X=`(/usr/bin/time -f "%[p][l]R" -p ./ej4 < "$file" > /dev/null) 2>&1 | grep real`
  Z="real"
  Y=${X#"$Z"}
  echo "${Y}" >> tiempos.out
  done

