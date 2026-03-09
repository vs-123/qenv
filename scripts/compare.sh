#!/bin/bash

echo "[INFO] BENCHMARKING QENV"
time -v ./qenv > /dev/null 2> qenv-v.txt

echo "[INFO] BENCHMARKING ENV"
time -v env > /dev/null 2> env-v.txt

echo "===  QENV  ==="
cat qenv-v.txt
echo "===  ENV  ==="
cat env-v.txt
