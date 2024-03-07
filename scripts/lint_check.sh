#!/bin/bash

file=splint_output.txt
rm -rf $file

files=$(find ./../HWIO -name '*.c' -o -name '*.cpp' -o -name '*.h')
while IFS= read -r line; do
    splint -weak -I../HWIO -I../TMR $line -unrecog +posixlib >> $file
done <<< "$files"

files=$(find ./../TMR -name '*.c' -o -name '*.cpp' -o -name '*.h')
while IFS= read -r line; do
    splint -weak -I../HWIO -I../TMR $line -unrecog +posixlib >> $file
done <<< "$files"

files=$(find ./../ReadPeriodic/src -name '*.c' -o -name '*.cpp' -o -name '*.h')
while IFS= read -r line; do
    splint -weak -I../HWIO -I../TMR $line -unrecog +posixlib >> $file
done <<< "$files"

filesize=$(wc -c $file | cut -d' ' -f1)
if (( $filesize != 0 )) ; then
    cat $file
    rm -rf $file
    echo ">>>>>>>>>>>>>>>>>>>>>>>> splint failed <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
    exit 1
fi

rm -rf $file

exit 0
