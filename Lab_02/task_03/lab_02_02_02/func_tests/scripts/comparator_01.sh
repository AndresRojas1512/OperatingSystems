#!/bin/bash

file_content_01=$(cat "$1")
file_content_02=$(cat "$2")
file_result_01=$(grep -oz 'Result:.*' <<<"$file_content_01" | tr -d '\0')
file_result_02=$(grep -oz 'Result:.*' <<<"$file_content_02" | tr -d '\0')

if [ -z "$file_result_01" ] || [ -z "$file_result_02" ]; then
    exit 1
fi

if [ "$file_result_01" = "$file_result_02" ]; then
    exit 0
else
    exit 1
fi