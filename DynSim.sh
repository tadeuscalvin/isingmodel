#!/bin/bash

MODE=0
L=800

while getopts ":l:m:" opt; do
    case $opt in
	l)
	    L=$OPTARG
	    ;;
	m)
	    MODE=$OPTARG
	    ;;
	\?)
	    echo "Invalid option: -$OPTARG" >&2
	    exit 1
	    ;;
	:)
	    echo "Option -$OPTARG requires an argument." >&2
	    exit 1
	    ;;
    esac
done

gcc DynSimOpenGL.c -lm -lGL -lglfw -Dmo=$MODE -DTAM=$L -o DynSim
./DynSim
