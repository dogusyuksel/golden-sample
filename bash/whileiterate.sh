#!/bin/bash

files=$(find . -name '*')
while IFS= read -r line; do
    echo "`basename "$line"`"
done <<< "$files"

