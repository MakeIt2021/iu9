#!/bin/bash

if [ ! -d "$1" ]; then
    echo "usage: ./non_empty /path/to/directory"
    exit 1
fi

FILES=$(find "$1" -type f \( -name "*.c" -o -name "*.h" \))

COUNTER=0

for file in $FILES; do
    LINES_COUNTER=$(grep -cve '^[[:space:]]*$' "$file") # -c -- подсчет строк, -v -- инвертирует результат, -e -- шаблон для поиска
    COUNTER=$((COUNTER+LINES_COUNTER))
done

echo "$COUNTER"