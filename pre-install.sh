#!/bin/bash
echo "Installing dependencies, sudo password may be required."
sudo apt update
sudo apt install -y build-essential cmake g++ nasm clang clang-format cppcheck pkg-config alsa-base alsa-utils libasound2-dev qtbase5-dev qtbase5-dev-tools qttools5-dev qttools5-dev-tools libqt5core5a libqt5gui5 libqt5widgets5 flex bison javacc libopus0 libopus-dev opus-tools libogg0 libogg-dev vorbis-tools doxygen libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev libfreetype6-dev libssl-dev libxmp-dev libfluidsynth-dev libwavpack-dev libjpeg-dev gpp cpp gcc-10 g++-10 clang-11
sudo apt upgrade -y
mkdir dependencies
cd dependencies
../install-sdl.sh
../install-sdl-image.sh
../install-opus.sh
../install-opusfile.sh
sudo cp /usr/local/lib/cmake/opusfile/OpusFileTargets.cmake /usr/local/lib/cmake/opusfile/opusfileTargets.cmake
sudo cp /usr/local/lib/cmake/opusfile/OpusFileTargets-noconfig.cmake /usr/local/lib/cmake/opusfile/opusfileTargets-noconfig.cmake
../install-sdl-mixer.sh
../install-sdl-ttf.sh
echo "Pre dependencies installed"
