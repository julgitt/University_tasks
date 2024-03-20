# find all .mp3 files in music directory
index=1
records=()
mp3_files=()
while read -r line; do
	mp3_files+=("$line")
	records+=("$index")
	records+=("$(mp3info -p "%l (%a): %t" "$line")")
	(( ++index ))
done < <(find . -name "*.mp3")

while CHOICE=$(zenity --title="Choose a song to play" --text="Music player" --list --column="Song number" --column="Song name" --width=600 --height=400 "${records[@]}"); do
	clear
    if zenity --question --text="Are you sure you want to play this song?"; then
    	echo "You're playing: ${records[$(( 2 * CHOICE - 1 ))]}"
    	mpg123 --quiet "${mp3_files[(( CHOICE - 1 ))]}"
    fi
done
clear
