#!/bin/bash
echo "Installing SDL2-mixer"
git clone git@github.com:libsdl-org/SDL_mixer.git || echo "Error: git clone failed, check your internet connection"
cd SDL_mixer  || echo "Error: SDL2_mixer directory not found"
git checkout release-2.8.0
mkdir build || echo "Error: build directory could not be created or already exists" | exit 1
cd build || echo "Error: build directory not found" | exit 1
cmake -DCMAKE_INSTALL_PREFIX=/usr .. || echo "Error: cmake configuring failed" | exit 1
cmake --build . || echo "Error: cmake build failed" | exit 1
sudo cmake --install . || echo "Error: cmake install failed" | exit 1
echo "SDL2_mixer installed"

