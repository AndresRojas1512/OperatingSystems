#!/bin/bash

CURRENT_DIR="./*.sh"
SCRIPTS_DIR="./func_tests/scripts/*.sh"

for SCRIPT in $CURRENT_DIR $SCRIPTS_DIR; do
    shellcheck "$SCRIPT"
done