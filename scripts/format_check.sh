#!/bin/bash

files=$(find ./../HWIO -name '*.c' -o -name '*.cpp' -o -name '*.h')
while IFS= read -r line; do
    clang-format -verbose -i -style=file --Werror $line
done <<< "$files"

files=$(find ./../TMR -name '*.c' -o -name '*.cpp' -o -name '*.h')
while IFS= read -r line; do
    clang-format -verbose -i -style=file --Werror $line
done <<< "$files"

files=$(find ./../ReadPeriodic/src -name '*.c' -o -name '*.cpp' -o -name '*.h')
while IFS= read -r line; do
    clang-format -verbose -i -style=file --Werror $line
done <<< "$files"

./dirty_check.sh

if [ $? -eq 0 ]
then
    exit 0
fi

exit 1
