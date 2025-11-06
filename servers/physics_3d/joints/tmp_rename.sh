#!/bin/bash

# Check if two arguments (search string and replace string) are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <search_string> <replace_string>"
    exit 1
fi

SEARCH_STRING="$1"
REPLACE_STRING="$2"

# Loop through all files in the current directory
for filename in *; do
    # Check if the filename is a regular file and contains the search string
    if [ -f "$filename" ] && [[ "$filename" == *"$SEARCH_STRING"* ]]; then
        # Create the new filename by replacing the search string
        new_filename="${filename//$SEARCH_STRING/$REPLACE_STRING}"

        # Rename the file
        if [ "$filename" != "$new_filename" ]; then
            mv "$filename" "$new_filename"
            echo "Renamed '$filename' to '$new_filename'"
        fi
    fi
done