#!/bin/bash

if [[ ! -p /tmp/mylog.fifo ]]; then
    mkfifo /tmp/mylog.fifo
fi


while true; do
    while read -r line; do
        echo "$(date +'%Y-%m-%d %H:%M:%S') $line"
    done < /tmp/mylog.fifo
done

