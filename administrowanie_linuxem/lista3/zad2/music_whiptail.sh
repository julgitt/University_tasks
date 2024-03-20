#!/bin/bash

index=1
records=()
mp3_files=()
while read -r line; do
	mp3_files+=("$line")
	records+=("$index")
	records+=("$(mp3info -p "%l (%a): %t" "$line")")
	(( ++index ))
done < <(find . -name "*.mp3")

while CHOICE=$(whiptail --menu "Choose a song to play" 25 78 16 "${records[@]}" 3>&1 1>&2 2>&3); do
	if [ -z "$CHOICE" ]; then
		clear
		echo "No option was chosen"
	else
		clear
		echo "You're playing: ${records[$(( 2 * CHOICE - 1 ))]}"
		mpg123 --quiet "${mp3_files[(( CHOICE - 1 ))]}"
	fi
done
clear
