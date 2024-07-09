#!/bin/bash

set -xe

clang -Wall -Wextra -o golGUI golGUI.c -lraylib -lm

