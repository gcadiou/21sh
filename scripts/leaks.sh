#!/bin/sh

trap '{ echo "\nKeyboard Interrupt detected." ;
		rm -f leaks.tmp
		sleep 0.5 ;
		exit 1; }' INT

[ $# -eq 0 ] && { echo "Usage: $0 < pid | partial-executable-name >"; exit 1; }

while true; do
	
	leaks $1 > leaks.tmp
	RES=$?
	
	if [ $RES -eq 1 ]; then
		printf "\033[31m"
	else
		printf "\033[32m"
	fi
	cat leaks.tmp | grep "total leaked bytes"
	printf "\033[0m"
	
	sleep 1;

done
