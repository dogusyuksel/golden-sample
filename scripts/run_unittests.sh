#!/bin/bash

current_dir=$(pwd)

files=$(find ../ -name 'project.yml')
while IFS= read -r line; do
    parentdir="$(dirname "$line")"
    echo ""
    echo "============== navigating $parentdir directory =============="
    cd $current_dir/$parentdir

    ceedling clean
    ceedling test:all

    retval=$?
    if [ $retval -ne 0 ]
    then
        echo "returning fail:$retval"
        exit $retval
    else
        echo "============== leaving $parentdir directory successfully =============="
    fi
done <<< "$files"

echo "returning success"
exit 0
