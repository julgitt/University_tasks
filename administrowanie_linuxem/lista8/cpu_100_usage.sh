##!/bin/bash

function infinite_fun {
    sum=0
    while true; do
        sum=$((sum + 1))
    done
}

for _ in $(seq 1 $1); do
    infinite_fun &
done

echo "Running $1 processes"
wait
