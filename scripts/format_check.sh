#!/bin/bash

source="./../"

if [ "$#" -eq 1 ]; then
    source=$1
fi

files=$(find $source -name '*.c' -o -name '*.cpp' -o -name '*.h')
while IFS= read -r line; do
    if [[ "$line" != *"test_"* ]] && [[ "$line" != *"thirdparty"* ]]; then
        clang-format -verbose -i -style=file --Werror $line
    fi
done <<< "$files"

./dirty_check.sh

if [ $? -eq 0 ]
then
    exit 0
fi

exit 1
