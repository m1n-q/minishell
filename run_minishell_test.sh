#!/bin/zsh
export a='ls -l'
export b='ls -l '
export c=' wc -l'
export d=' wc -l '

mkfifo input
python3 testcase.py > input &
./minishell < input
rm input
