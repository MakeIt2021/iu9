#!/bin/bash

if [ $# -ne 2 ]; then
    echo "usage: ./long_lasting /path/to/program interval"
    exit 1
fi

PROGRAM=$1
DELAY=$2

if [ ! -x "$PROGRAM" ]; then
    echo "usage: ./long_lasting /path/to/program interval"
    exit 1
fi

if ! [[ "$DELAY" =~ ^[0-9]+$ ]]; then # не число?
    echo "usage: ./long_lasting /path/to/program interval"
    exit 1
fi

TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
        
LOGFILE="output_${TIMESTAMP}.log"
ERRFILE="errors_${TIMESTAMP}.log"

PID=-1
while true; do
    if [[ "$PID" =~ ^[0-9]+$ ]] && ps -p "$PID" > /dev/null 2>&1; then # проверяем, запущен ли процесс, перенаправляем вывод ps в чёрную дыру     
        echo "$(date): program is already running, waiting..."   
    else
        echo "$(date): starting program now."
        bash "$PROGRAM" 1>>"$LOGFILE" 2>>"$ERRFILE" &

        PID=$!
    fi

    sleep $((DELAY * 60))
done