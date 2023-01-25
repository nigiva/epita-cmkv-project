#!/bin/bash

echo "Checking with reference files..."
for size in {2..6}; do
  for i in {1..9}; do
        refpath="data/ref/s$size-0$i-ref.txt"
        exportpath="export/s$size-0$i.txt"
        filename=${refpath#data/ref/}
        diff -q "$refpath" "$exportpath"
    done
done

echo "All done !"