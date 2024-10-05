#!/bin/bash

file_stream_in="$1"
run_command="../../app.exe"
output_file="out.txt"

if [ -n "$USE_VALGRIND" ]; then
    valgrind $run_command < "$file_stream_in" > "$output_file"
else
    $run_command < "$file_stream_in" > "$output_file" && exit 1 || exit 0
fi