#!/bin/bash 
for i in `seq 1 100`; 
do 
	bash ./Grader.sh 2> /dev/null | grep -o "Final Grade [0-9][0-9][/][0-9][0-9]" 
done
	
for i in `seq 1 100`; 
do 
	bash ./Grader2.sh 2> /dev/null | grep -o "Final Grade [0-9][0-9][/][0-9][0-9]" 
done
