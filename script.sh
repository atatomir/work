#!/bin/bash
echo "Start script"
for entry in `ls`; do 
    if [ -d $entry ] ; then 
        for src in `ls $entry`; do 
            echo ----------------------------- $entry ---------------------------
            g++ $entry/$src -o mytest 
            echo ----------------------------------------------------------------
            echo " "  
        done
    fi
done
#
