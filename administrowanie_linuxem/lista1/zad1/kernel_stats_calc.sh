#!/bin/bash

ARCHIVE_PATH="./kernels"
RESULTS_PATH="./results"

versions=("0.99.15-1993" "1.1.95-1995" "2.0.27-1997" "2.0.36-1999" "2.2.18-2001" "2.4.20-2003" "2.6.10-2005" "2.6.19-2007" "2.6.28-2009" "2.6.36-2011" "3.7.1-2013" "3.18-2015" "4.9-2017" "4.20-2019" "5.10-2021" "6.1.1-2023")

for version in "${versions[@]}"
do
  echo "Calculating $version version stats..."
  
  ARCHIVE="$ARCHIVE_PATH/linux-$version.tar.gz"
  if [ -f "$ARCHIVE" ]; then
    DIRECTORY="$ARCHIVE_PATH/linux-$version"
    mkdir -p "$DIRECTORY"
    tar -xzf "$ARCHIVE" -C "$DIRECTORY"
    
    if [ -d "$DIRECTORY" ]; then
      mkdir -p "$RESULTS_PATH/$version"
      
      echo "Making cloc calculations..."
      cloc "$DIRECTORY" --out="$RESULTS_PATH/$version/cloc_results.txt"
      
      echo "Making sloccount calculations..."
      sloccount "$DIRECTORY" > "$RESULTS_PATH/$version/sloccount_results.txt"
    else
      echo "Failed to create the directory: $DIRECTORY"
    fi
  else
    echo "Archive $ARCHIVE does not exist."
  fi
done

