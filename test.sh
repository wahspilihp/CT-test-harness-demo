#!/bin/bash

program_name=./a.out
test_dir=tests

for d in "$test_dir"/* ;do 
	if env STEAL_DEAL_CHOICES="$d/computer.txt" "$program_name" < "$d/in.txt" | diff "$d/out.txt" - 
	then
		echo Passed test in $d
	else
		echo -e '\n\n\n\n\n\n\n' Failed test in $d !!!!!!!!!!!!!!!!!!!!!!!!
		env STEAL_DEAL_CHOICES="$d/computer.txt" "$program_name" < "$d/in.txt" | colordiff -W $COLUMNS -y "$d/out.txt" -
		echo -e '\n\n\' Failed test in $d !!!!!!!!!!!!!!!!!!!!!!!! '\n\n'
	fi
done