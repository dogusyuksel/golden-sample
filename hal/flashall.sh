#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "type project name"
    exit 1
fi

files=$(find . -name '*' -type d -maxdepth 1 -mindepth 1)
while IFS= read -r line; do
    dirname=$(basename "$line")

    if [[ $dirname =~ $1 ]]; then
        cd  $dirname/build
        st-flash write *.bin 0x08000000
        cd ../..
        exit 0
    fi
done <<< "$files"

echo "be careful about the argument syntax"
exit 1
