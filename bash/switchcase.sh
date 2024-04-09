#!/bin/bash

DEPARTMENT="Electronics and Communication"

echo -n "Your DEPARTMENT is "

case $DEPARTMENT in

  "Computer Science")
    echo "Computer Science"
    ;;

   "Electrical and Electronics Engineering" | "Electrical Engineering")
    echo "Electrical and Electronics Engineering or Electrical Engineering"
    ;;

  "Information Technology" | "Electronics and Communication")
    echo "Information Technology or Electronics and Communication"
    ;;

  *)
    echo "Invalid"
    ;;
esac

