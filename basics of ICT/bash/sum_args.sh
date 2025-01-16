#!/bin/bash

sum_args() {
  if [ $# -lt 2 ]; then
    echo "usage: sum x1 ... xN"
    
  fi
  
  sum=0
  while [ $# -gt 0 ]; do
    sum=$((sum+$1))
    shift
  done
    
  echo $sum
}

sum_args "$@"
