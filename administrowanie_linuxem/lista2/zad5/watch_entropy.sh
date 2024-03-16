#!/bin/bash

while true; do
	poolsize=$(cat "/proc/sys/kernel/random/poolsize")
	entropy=$(cat "/proc/sys/kernel/random/entropy_avail")
	
	printf "Available entropy: %s/%s\r" "$entropy" "$poolsize"
	
	read -rs -n 1 -t 1 && break
	
done 

echo ""
