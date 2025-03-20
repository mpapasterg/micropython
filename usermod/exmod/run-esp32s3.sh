#! /usr/bin/env bash

echo "Install dependencies"
# sudo dnf install libffi-devel pkg-config

echo "Clone and install the ESP-IDF"
cd $HOME/Source
git clone https://github.com/espressif/esp-idf.git
git checkout release/v5.4
cd $HOME/Source/esp-idf
git submodule update --init --recursive
./install.sh all
source export.sh

echo "Build the mpy-cross cross compiler"
cd $HOME/Code/micropython
make -C mpy-cross

echo "Get into ports/exp32 to enter the ESP32 port"
cd $HOME/Code/micropython/ports/esp32

echo "Clean previous builds before restarting"
make clean

echo "Compile required submodules"
make BOARD=ESP32_GENERIC_S3 BOARD_VARIANT=SPIRAM_OCT submodules

echo "Compile the port with the MicroPython C module"
make BOARD=ESP32_GENERIC_S3 BOARD_VARIANT=SPIRAM_OCT USER_C_MODULES=$HOME/Code/micropython/usermod CFLAGS_EXTRA=-DMODULE_EXMOD_ENABLED=1 all

echo "Run the MicroPython interpreter locally"
