#!/bin/bash

mapfile -d $'\0' mp3_files < <(find . -name "*.mp3" -print0)

entries=()
for file in "${mp3_files[@]}"; do
	entries+=("$(mp3info -p "%l (%a): %t" "$file")")
done

PS3="Choose a number to play> "
IFS=$'\n'   # Ustawienie separatora na znak nowej linii
select song in "${entries[@]}"; do
	if [ -n "$song" ]; then
		mplayer "${mp3_files[$REPLY - 1]}"
	else
		echo "Invalid selection. Please choose a valid number."
	fi
done
