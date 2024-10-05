#!/bin/bash

SOURCE_FILE=main.c
OUT_FILE=app.exe

gcc -std=c99 -g -Wall -Werror -Wextra -Wunused -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla --coverage -fprofile-arcs -ftest-coverage -c $SOURCE_FILE -o ${SOURCE_FILE%.c}.o -lm
gcc -std=c99 -g -Wall -Werror -Wextra -Wunused -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla --coverage -fprofile-arcs -ftest-coverage ${SOURCE_FILE%.c}.o -o $OUT_FILE -lm