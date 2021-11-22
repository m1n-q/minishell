#!/bin/zsh

export a='ls -l'
export b='ls -l '
export c=' wc -l'
export d=' wc -l '

mkfifo input2
python3 testcase_bash.py > input2 &
bash < input2
rm input2
