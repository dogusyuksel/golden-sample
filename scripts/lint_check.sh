#!/bin/bash

file=splint_output.txt
rm -rf $file

files=$(find ./../ceedling -name '*.c' -o -name '*.cpp' -o -name '*.h')
while IFS= read -r line; do
    if [[ "$line" != *"test"* ]]; then
        splint -weak -I../ceedling/hwdependentcode -I../ceedling/thirdpartycode -I../ceedling/myproject $line -unrecog +posixlib >> $file
    fi
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
