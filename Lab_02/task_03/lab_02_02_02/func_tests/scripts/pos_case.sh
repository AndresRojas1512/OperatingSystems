#!/bin/bash

file_stream_in="$1"
file_stream_out_expect="$2"
output_file="out.txt"
run_command="../../app.exe"

if [ -n "$USE_VALGRIND" ]; then
    valgrind $run_command < "$file_stream_in" > "$output_file"
else
    $run_command < "$file_stream_in" > "$output_file"
fi

./comparator.sh "$output_file" "$file_stream_out_expect"