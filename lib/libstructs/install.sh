#!/bin/bash
echo "**** Cleaning .o ****"
make clean
echo "**** Compiling lib ****"
make
echo "**** Libstructs correctly installed ****"
