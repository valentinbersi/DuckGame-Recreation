#!/bin/bash
echo "Installing SDL2-image"
git clone git@github.com:libsdl-org/SDL_image.git
git checkout release-2.8.2
cd SDL_image
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
echo "SDL2-image installed"

