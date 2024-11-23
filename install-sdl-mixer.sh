#!/bin/bash
echo "Installing SDL2-mixer"
git clone git@github.com:libsdl-org/SDL_mixer.git
git checkout release-2.8.0
cd SDL_mixer
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
echo "SDL2-mixer installed"

