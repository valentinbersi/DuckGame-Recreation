#!/bin/bash
echo "Installing libsdl2pp"
git clone https://github.com/libSDL2pp/libSDL2pp.git || echo "Error: git clone failed, check your internet connection"
cd libSDL2pp || echo "Error: libSDL2pp directory not found"
git checkout 0.18.1
mkdir build || echo "Error: build directory could not be created or already exists" | exit 1
cd build || echo "Error: build directory not found" | exit 1
cmake cmake -DCMAKE_INSTALL_PREFIX=/usr .. || echo "Error: cmake configuring failed" | exit 1
cmake --build . || echo "Error: cmake build failed" | exit 1
sudo cmake --install . || echo "Error: cmake install failed" | exit 1
echo "libsdl2pp installed"

