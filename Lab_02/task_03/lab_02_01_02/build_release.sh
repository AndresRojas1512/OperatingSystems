#!/bin/bash

SOURCE_FILE=main.c
OUT_FILE=app1.out

gcc -std=c99 -Wall -Werror -Wextra -Wunused -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -c $SOURCE_FILE -o ${SOURCE_FILE%.c}.o -lm
gcc -std=c99 -Wall -Werror -Wextra -Wunused -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla ${SOURCE_FILE%.c}.o -o $OUT_FILE -lm
