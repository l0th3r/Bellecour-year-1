#!/bin/sh

MEMCHECK=`cat memcheck.log | grep -v PR_SET_PTRACER`

echo -n Memory check... 
if [ -z "$MEMCHECK" ]
then
	echo -e "\e[1;32m OK \e[0m "
else
	echo -e "\e[1;31m failed \e[0m "
	cut -f5 -d'=' memcheck.log | grep -v PR_SET_PTRACER
fi
rm memcheck.log*
