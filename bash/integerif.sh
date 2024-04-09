#!/bin/bash

a=4
b=5

if [ "$a" -eq "$b" ]
then
    echo "is equal to"
fi

if [ "$a" -ne "$b" ]
then
    echo "is not equal to"
fi

if [ "$a" -gt "$b" ]
then
    echo "is greater than"
fi

if [ "$a" -ge "$b" ]
then
    echo "is greater than or equal to"
fi

if [ "$a" -lt "$b" ]
then
    echo "is less than"
fi

if [ "$a" -le "$b" ]
then
    echo "is less than or equal to"
fi

if (("$a" < "$b"))
then
    echo "is less than"
fi

if (("$a" <= "$b"))
then
    echo "is less than or equal to"
fi

if (("$a" > "$b"))
then
    echo "is greater than"
fi

if (("$a" >= "$b"))
then
    echo "is greater than or equal to"
fi

