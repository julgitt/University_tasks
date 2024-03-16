#!/bin/bash

total_size=0

if [[ $# -ne 2 ]]; then
    echo "Wrong number of arguments: expected 2 arguments."
    exit 1
fi

limit=$1
path=$2

files=$(find "$path" -type f -printf "%C@\t%s\t%p\n" | sort)

while IFS=$'\t' read -r file_modification_date size filename; do
    (( total_size += size ))
done <<< "$files"

echo "Total files size in directory: $total_size"
echo ""
	
while IFS= read -r file; do
	filename=$(echo "$file" | awk -F'\t' '{print $3}')
	size=$(echo "$file" | awk -F'\t' '{print $2}')
	if [[ "$total_size" -gt "$limit" ]]; then
    	(( total_size -= size ))
    	echo "You should delete $filename file of size $size"
    else
   		echo ""
    	break
    fi
done <<< "$files"

