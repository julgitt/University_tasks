#!/bin/bash

if [[ ! -p /tmp/mylog.fifo ]]; then
    echo "Pipe /tmp/mylog.fifo does not exist."
    exit 1
fi


while true; do
	system_info=$(uname -a)

	diagnostic_message="System - $system_info"

	echo "$diagnostic_message" > /tmp/mylog.fifo
	
	sleep 10000
done
