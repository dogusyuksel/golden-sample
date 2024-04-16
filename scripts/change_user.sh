#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "please type full path of the directory"
    exit 1
fi

groupnames=$(groups)
readarray -d " " -t strarr <<< "$groupnames"
groupname=${strarr[0]}

username=$(whoami)

files=$(find $1 -name '*')
while IFS= read -r line; do
    lsresult=$(ls -al $line)
    if [[ "${lsresult}" == *"root"* ]] ;then
        echo "$lsresult"
    
        readarray -d " " -t strarr <<< "$lsresult"
        filename=${strarr[-1]}
        filenamelast=$(echo -n "$filename")
        echo $filenamelast

        sudo chown -R $username  $filenamelast
        sudo chgrp -R $groupname $filenamelast
    fi
done <<< "$files"

exit 0
