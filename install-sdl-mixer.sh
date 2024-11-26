#!/bin/bash
echo "Installing SDL2-mixer"
git clone git@github.com:libsdl-org/SDL_mixer.git
cd SDL_mixer
git checkout release-2.8.0
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
echo "SDL2-mixer installed"

