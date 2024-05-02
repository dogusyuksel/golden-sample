#!/bin/bash

files=$(find . -name '*' -type d -maxdepth 1 -mindepth 1)
while IFS= read -r line; do
    dirname=$(basename "$line")

    if [[ $# -eq 1 ]]; then
        if [[ $dirname =~ $1 ]]; then
            rm -rf  $dirname/build
            exit 0
        fi
    fi

    if [[ $# -eq 0 ]]; then
        rm -rf  $dirname/build
    fi
done <<< "$files"

if [[ $# -eq 1 ]]; then
    echo "be careful about the argument syntax"
    exit 1
fi

exit 0
