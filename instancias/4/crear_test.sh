#!/bin/bash

while IFS=$'\r' read -r line; do
  echo "$line" > "tmp"
  ./intervalosRandom < tmp > "./$line.txt"
  echo "----"
done < "$1"
rm tmp
