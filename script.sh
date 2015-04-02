#!/bin/bash
echo "Start script"
for entry in `ls _infoarena/`; do 
    if [ -d _infoarena/$entry ] ; then 
        for src in `ls _infoarena/$entry`; do 
            echo ----------------------------- $entry ---------------------------
            g++ _infoarena/$entry/$src -o mytest 
            echo ----------------------------------------------------------------
            echo " "  
        done
    fi
done
#
