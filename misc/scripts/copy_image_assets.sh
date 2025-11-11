#!/bin/bash

if [[ -z "$1" ]] || [[ -z "$2" ]]; then
    echo "Usage: misc/scripts/copy_image_assets.sh SOURCE_DIR DEST_DIR"
    echo "Example: misc/scripts/copy_image_assets.sh ./assets/images ./build/images"
    exit 0
fi


SOURCE_DIR="$1"  # Replace with your source directory
DEST_DIR="$2" # Replace with your destination directory

# Create the destination directory if it doesn't exist
mkdir -p "$DEST_DIR"

# Find all image files (e.g., .jpg, .png, .gif) in the source directory and its subfolders
# and copy them to the corresponding location in the destination directory,
# creating subdirectories as needed.
find "$SOURCE_DIR" -type f \( -name "*.jpg" -o -name "*.jpeg" -o -name "*.png" -o -name "*.svg" -o -name "*.gif" \) -print0 | while IFS= read -r -d $'\0' file; do
    # Calculate the relative path from the source directory
    relative_path="${file#$SOURCE_DIR/}"
    
    # Determine the destination path for the file
    dest_file="$DEST_DIR/$relative_path"
    
    # Create the parent directory in the destination if it doesn't exist
    mkdir -p "$(dirname "$dest_file")"
    
    # Copy the image file
    cp "$file" "$dest_file"
done