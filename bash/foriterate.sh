#!/bin/bash


files=$(find . -name '*')
for line in $files
do
  echo "`basename "$line"`"
done
