#!/bin/bash

DATA_DIR="../data"
POS_PREFIX="pos_"
NEG_PREFIX="neg_"

echo "Running positive tests..."
for input_file in "$DATA_DIR"/"$POS_PREFIX"*_in.txt; do
    expected_output="${input_file/_in/_out}"
    if [ -f "$input_file" ]; then
        echo -n "Testing $input_file..."
        if ./pos_case.sh "$input_file" "$expected_output"; then
            echo "PASSED"
        else
            echo "FAILED"
        fi
    else
        echo "Skipping missing input: $input_file"
    fi
done

echo "Running negative tests..."
for input_file in "$DATA_DIR"/"$NEG_PREFIX"*_in.txt; do
    if [ -f "$input_file" ]; then
        echo -n "Testing $input_file..."
        if ./neg_case.sh "$input_file"; then
            echo "PASSED"
        else
            echo "FAILED"
        fi
    else
        echo "Skipping missing input: $input_file"
    fi
done

gcov main.c