#!/bin/bash

var=1
var=$((var+1))
((var=var+1))
((var+=1))
((var++))

echo "$var"
