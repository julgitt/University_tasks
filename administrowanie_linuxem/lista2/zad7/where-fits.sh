#!/bin/bash

files=("$@")
total_size=0

for file in "${files[@]}"; do
    if [ ! -e "$file" ]; then
        echo "File or directory '$file' does not exist."
        continue
    fi

    (( total_size += $(du -s "$file" | awk '{print $1}') ))
done

echo "Total files size: $total_size"
echo ""

echo "Filesystems: "

mounts=$(df -P | tail -n +2)

while IFS= read -r mount; do
	name=$(echo "$mount" | awk '{print $1}')
	available_space=$(echo "$mount" | awk '{print $4}')
    if [ "$available_space" -gt "$total_size" ]; then
        echo "$name"
    fi
done <<< "$mounts"


