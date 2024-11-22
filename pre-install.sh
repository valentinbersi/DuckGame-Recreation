#!/bin/bash
echo "Installing dependencies, sudo password may be required."
sudo apt update
sudo apt install -y build-essential cmake g++ nasm clang clang-format cpplint cppcheck pre-commit
sudo apt upgrade -y
echo "Pre dependencies installed"
