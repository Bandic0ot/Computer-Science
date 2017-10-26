#!/bin/bash

# Sean Robson-Kullman
# skr519
# 11182480
# Matthew Mulenga
# mam558
# 11144528

# Tar all the needed files.
tar -cvf xv6-a1.tar /xv6-public
tar -cvf group40-a1handin.tar *.c *.h *.txt Makefile partB.bash xv6-a1.tar

rm xv6-a1.tar
