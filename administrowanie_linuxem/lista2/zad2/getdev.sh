#!/bin/bash

if [ $# -eq 0 ]; then
    args=false
else
	mount_point=$(echo "$1" | sed 's:/*$:/:')
	args=true
fi

while IFS= read -r line; do

    if [[ -z "$line" || "${line:0:1}" = "#" ]]; then
        continue
    fi

    fields=($line)
    
    cur_mount_point=$(echo "${fields[1]}" | sed 's:/*$:/:')
    
    if [[ "$cur_mount_point" = "$mount_point" || "$args" != true ]]; then
        echo "Device: ${fields[0]}"
        echo "Filesystem type: ${fields[2]}"
        echo "Mount options: ${fields[3]}"
        echo "Dump frequency: ${fields[4]}"
        echo "Fsck pass number: ${fields[5]}"
        if [ "$args" = true ]; then
            exit 0
        fi
        echo "Mount point: ${fields[1]}"
        echo ""
    fi
done < /etc/fstab

if [ "$args" != true ]; then
	exit 0
fi

echo "No entry found for $mount_point in /etc/fstab"
exit 1
