#!/bin/bash

if [ -f app.exe ]; then
    rm app.exe
fi

if [ -f func_tests/scripts/out.txt ]; then
    rm func_tests/scripts/out.txt
fi

if [ -d report ]; then
    rm -r report
fi

for file in *.gcda; do
    if [ -f "$file" ]; then
        rm "./$file"
    fi
done

for file in *.gcno; do
    if [ -f "$file" ]; then
        rm "./$file"
    fi
done

for file in *.gcov; do
    if [ -f "$file" ]; then
        rm "./$file"
    fi
done

for file in *.o; do
    if [ -f "$file" ]; then
        rm "./$file"
    fi
done

for file in *.info; do
    if [ -f "$file" ]; then
        rm "./$file"
    fi
done