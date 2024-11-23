#!/bin/bash
echo "Installing SDL2-ttf"
git clone https://github.com/libsdl-org/SDL_ttf.git
git checkout release-2.22.0
cd SDL_ttf
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
echo "SDL2-ttf installed"

