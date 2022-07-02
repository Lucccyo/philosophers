#!/bin/bash
N="$1"
shift
norminette
gcc -Wall -Wextra -pthread ./$N
