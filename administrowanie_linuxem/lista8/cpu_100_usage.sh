##!/bin/bash

function infinite_fun {
    sum=0
    while true; do
        sum=$((sum + 3))
        sum=$((sum / 2))
    done
}

for _ in $(seq 1 $1); do
    infinite_fun &
done

echo "Running $1 processes"
wait
