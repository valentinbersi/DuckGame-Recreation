#!/bin/bash
echo "Installing SDL2-ttf"
git clone https://github.com/libsdl-org/SDL_ttf.git || echo "Error: git clone failed, check your internet connection"
cd SDL_ttf || echo "Error: SDL_ttf directory not found"
git checkout release-2.22.0
mkdir build || echo "Error: build directory could not be created or already exists" | exit 1
cd build || echo "Error: build directory not found" | exit 1
cmake .. || echo "Error: cmake configuring failed" | exit 1
cmake --build . || echo "Error: cmake build failed" | exit 1
sudo cmake --install . || echo "Error: cmake install failed" | exit 1
echo "SDL2_ttf installed"

