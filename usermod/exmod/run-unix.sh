#! /usr/bin/env bash

echo "Install dependencies"
# sudo dnf install libffi-devel pkg-config

echo "Get into ports/unix to enter the UNIX port"
cd $HOME/Code/micropython/ports/unix

echo "Clean previous builds before restarting"
make clean

echo "Compile required submodules"
make submodules

echo "Compile the port with the MicroPython C module"
make USER_C_MODULES=$HOME/Code/micropython/usermodCFLAGS_EXTRA=-DMODULE_EXMOD_ENABLED=1 all

echo "Run the MicroPython interpreter locally"
./build-standard/micropython