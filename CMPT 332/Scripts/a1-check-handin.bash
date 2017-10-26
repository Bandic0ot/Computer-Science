#!/bin/bash

# Sean Robson-Kullman
# skr519
# 11182480
# Matthew Mulenga
# mam558
# 11144528

# Move the tar to a temporary folder.
mkdir a1-handin
mv group40-a1handin.tar a1-handin

# Switch to temp folder and untar everything.
cd a1-handin

tar -xvf group40-a1handin.tar
tar -xvf xv6-a1.tar

rm group40-a1handin.tar
rm xv6-a1.tar

make

cd xv6-public
make qemu-nox
