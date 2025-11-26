#!/bin/bash

if [[ -z "$(which python)" ]]; then
    echo "Python is not found in PATH. Exiting."
    exit 0
fi

if [[ -z "$1" ]]; then
    echo "no PATH to Tekisasu-Engine git directory provided in CLI argument."
    echo " Usage:"
    echo "  misc/scripts/rebase_headers.sh ROOT_DIR_OF_TEKISASU_ENGINE_GIT_REPO"
    echo "  "
    echo "Example:"
    echo "  cd /mnt/c/Dev/git/tekisasu" 
    echo "  misc/scripts/rebase_headers.sh ROOT_DIR_OF_TEKISASU_ENGINE_GIT_REPO"
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

HEADER_SCRIPT="$GIT_PATH/misc/scripts/copyright_headers.py"

# *.mm files
for folder in $(ls -d */ | grep -v pycache | grep -v thirdparty); do 
    echo $folder
    echo "---------------------------------------------"
    for file in $(find $folder -type f -name "*.mm"); do 
        echo "  $file"
        $HEADER_SCRIPT $file
    done
    echo " "
done

# *.cpp files
for folder in $(ls -d */ | grep -v pycache | grep -v thirdparty); do 
    echo $folder
    echo "---------------------------------------------"
    for file in $(find $folder -type f -name "*.cpp"); do 
        echo "  $file"
        $HEADER_SCRIPT $file
    done
    echo " "
done

# *.h files
for folder in $(ls -d */ | grep -v pycache | grep -v thirdparty); do 
    echo $folder
    echo "---------------------------------------------"
    for file in $(find $folder -type f -name "*.h"); do 
        echo "  $file"
        $HEADER_SCRIPT $file
    done
    echo " "
done

# *.inc files
for folder in $(ls -d */ | grep -v pycache | grep -v thirdparty); do 
    echo $folder
    echo "---------------------------------------------"
    for file in $(find $folder -type f -name "*.inc"); do 
        echo "  $file"
        $HEADER_SCRIPT $file
    done
    echo " "
done