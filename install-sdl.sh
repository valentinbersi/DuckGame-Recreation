#!/bin/bash
echo "Installing SDL2"
git clone git@github.com:libsdl-org/SDL.git
cd SDL
git checkout release-2.30.9
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
echo "SDL2 installed"

