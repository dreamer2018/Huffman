#!/bin/bash
if [ "$#" != "2" ];then
    echo "Usage: zpc filename1 filename2"
    exit 0
fi
if [ ! -e "$1" ];then
    echo "$1 Not Found !"
    exit 0
fi

if [ ! -e "$2" ];then
    echo "$2 Not Found !"
    exit 0
fi

diff $1 $2
