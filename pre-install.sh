#!/bin/bash
echo "Installing dependencies, sudo password may be required."
sudo apt update
sudo apt install -y build-essential cmake g++ nasm clang clang-format cpplint cppcheck pre-commit pkg-config alsa-base alsa-utils libasound2-dev qtbase5-dev qtbase5-dev-tools qttools5-dev qttools5-dev-tools libqt5core5a libqt5gui5 libqt5widgets5 flex bison javacc libopus0 libopus-dev opus-tools libogg0 libogg-dev vorbis-tools doxygen libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev
sudo apt upgrade -y
echo "Pre dependencies installed"
