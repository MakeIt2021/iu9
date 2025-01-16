#!/bin/bash

sum_even() {
  if [ $# -lt 2 ]; then
    echo "usage: sum_even x1 ... xN"
  fi

  sum=0
  while [ $# -gt 0 ]; do
    if [ $(($1 % 2)) -eq 0 ]; then
      sum=$((sum+$1))
    fi
    shift
  done
  
  echo $sum
}

sum_even "$@"

