#!/bin/sh

COLOR=0;

while [ $COLOR -lt 245 ]; do
	echo "$COLOR: \\033[38;5;${COLOR}mSAMPLE\\033[0m"
	((COLOR++));
done  
