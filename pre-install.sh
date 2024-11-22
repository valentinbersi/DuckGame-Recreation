#!/bin/bash
echo "Installing dependencies, sudo password may be required."
sudo apt update
sudo apt install -y build-essential cmake g++ nasm clang clang-format cpplint cppcheck pre-commit pkg-config alsa-base alsa-utils libasound2-dev qtbase5-dev qtbase5-dev-tools qttools5-dev qttools5-dev-tools libqt5core5a libqt5gui5 libqt5widgets5 flex bison javacc libopus-dev opus-tools libopus0 doxygen
sudo apt upgrade -y
echo "Pre dependencies installed"
