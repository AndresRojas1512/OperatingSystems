#!/bin/bash
file_01="$1"
file_02="$2"
temp_01=$(mktemp -t file1.XXXXXX.txt)
temp_02=$(mktemp -t file2.XXXXXX.txt)

grep -oE '[-+]?[0-9]+([,.][0-9]+)?([eE][-+]?[0-9]+)?' "$file_01" > "$temp_01"
grep -oE '[-+]?[0-9]+([,.][0-9]+)?([eE][-+]?[0-9]+)?' "$file_02" > "$temp_02"

if diff "$temp_01" "$temp_02" >/dev/null ; then
    rm -f "$temp_01" "$temp_02"
    exit 0
else
    rm -f "$temp_01" "$temp_02"
    exit 1
fi