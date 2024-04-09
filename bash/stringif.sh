#!/bin/bash

str="YeS"


if [[ "${str,,}" == *"yes"* ]] ;then
    echo "check for 'yes' in string (case insensitive):"
fi

if [[ "$(echo "$str" | tr '[:upper:]' '[:lower:]')" == *"yes"* ]] ;then
    echo "check for 'yes' in string (case insensitive):"
fi

if [[ "${str}" == *"yes"* ]] ;then
    echo "check for 'yes' in string (case sensitive):"
fi

if [[ "${str}" =~ "yes" ]] ;then
    echo "check for 'yes' in string (case sensitive):"
fi

if [[ "${str}" == "yes" ]] ;then
    echo "exact match (case sensitive):"
fi

if [[ "${str,,}" == "yes" ]] ;then
    echo "exact match (case insensitive):"
fi

if [ "$str" = "YeS" ] ;then
    echo "exact match:"
fi
