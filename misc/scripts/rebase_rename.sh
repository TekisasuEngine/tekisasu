#!/bin/bash
#!/bin/bash

# Directory to operate in (current directory by default)
TARGET_DIR="$1"

# String to find in filenames
OLD_STRING="$2"

# String to replace with
NEW_STRING="$3"

echo "Renaming files in $TARGET_DIR: Replacing \"$OLD_STRING\" with \"$NEW_STRING\"."

# Loop through all files in the target directory
for file in "$TARGET_DIR"/*; do
    # Check if it's a regular file (not a directory)
    if [ -f "$file" ]; then
        # Get the base filename
        filename=$(basename -- "$file")
        
        # Check if the filename contains the old string
        if [[ "$filename" == *"$OLD_STRING"* ]]; then
            # Construct the new filename
            new_filename="${filename//$OLD_STRING/$NEW_STRING}"
            
            # Construct the full paths for mv command
            old_path="$TARGET_DIR/$filename"
            new_path="$TARGET_DIR/$new_filename"
            
            # Rename the file
            mv "$old_path" "$new_path"
            echo "Processed: '$filename' to '$new_filename'"
        fi
    fi
done