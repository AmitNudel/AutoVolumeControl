#!/bin/sh

# Shared library for ALSA apps
if [ -x "$(command dpkg -s libasound2)" ]; then
    sudo apt-get install libasound2-dev
fi
# mpg123 player
if [ -x "$(command dpkg -s mpg123)" ]; then
    sudo apt-get install mpg123
fi
echo "____ _  _ ___ ____    _  _ ____ _    _  _ _  _ ____    ____ ____ _  _ ___ ____ ____ _"
echo "|__| |  |  |  |  |    |  | |  | |    |  | |\/| |___    |    |  | |\ |  |  |__/ |  | |"
echo "|  | |__|  |  |__|     \/  |__| |___ |__| |  | |___    |___ |__| | \|  |  |  \ |__| |___"
echo " "

cd AutoVolumeControlCode/
make

