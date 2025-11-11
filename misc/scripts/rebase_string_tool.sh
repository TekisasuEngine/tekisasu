#!/bin/bash

if [[ -z "$(which python)" ]]; then
    echo "Python is not found in PATH. Exiting."
    exit 0
fi

if [[ -z "$1" ]]; then
    echo "no PATH to Tekisasu-Engine git directory provided in CLI argument."
    echo " Usage:"
    echo "  misc/scripts/rebase_string_tool.sh ROOT_DIR_OF_TEKISASU_ENGINE_GIT_REPO OLD_STRING NEW_STRING"
    echo "  "
    echo "Example:"
    echo "  cd /mnt/c/Dev/git/tekisasu" 
    echo "  misc/scripts/rebase_string_tool.sh ROOT_DIR_OF_TEKISASU_ENGINE_GIT_REPO OLD_STRING NEW_STRING"
    echo " "
    echo "Exiting."
    echo " "
    exit 0
else
    GIT_PATH="$1"
fi

if [[ ! -f "$GIT_PATH/version.py" ]]; then
    echo "no valid Tekisasu Engine git repo path given."
    echo " (version.py in directory specified not found)"
    echo " "
    echo "Exiting."
    echo " "
    exit 0
fi

if [[ -z "$2" ]] && [[ -z "$3" ]]; then
    echo "no valid old/new string replacement values given."
    echo " Usage:"
    echo "  misc/scripts/rebase_string_tool.sh ROOT_DIR_OF_TEKISASU_ENGINE_GIT_REPO OLD_STRING NEW_STRING"
    echo "  "
    echo "Example:"
    echo "  cd /mnt/c/Dev/git/tekisasu" 
    echo "  misc/scripts/rebase_string_tool.sh ROOT_DIR_OF_TEKISASU_ENGINE_GIT_REPO OLD_STRING NEW_STRING"
    echo " "
    echo "Exiting."
    echo " "
    exit 0
fi

OLD_STRING="$2"
NEW_STRING="$3"

echo "'$OLD_STRING' -> '$NEW_STRING'"
echo "---------------------------------------------------------"
#echo "PROCEED? (y/n):"
#read value
value="y"

if [[ "$value" == "y" ]]; then
    for file in $(grep -F -l -r --exclude-dir=".git" $OLD_STRING . | grep -v "x86_64.obj" | grep -v "x86_64.lib" | grep -v pycache | grep -v "x86_64.exe" | grep -v "scripts"); do 
        sed -i -e "s/$OLD_STRING/$NEW_STRING/g" "$file"
        echo "processed: $file"
    done
elif [[ "$value" == "n" ]]; then
    echo "Exiting."
    echo " "
    exit 0
else
    echo "invalid input. Exiting."
    echo " "
    exit 0
fi

echo " "