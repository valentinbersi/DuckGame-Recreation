#!/bin/bash
echo "Installing libsdl2pp"
git clone https://github.com/libSDL2pp/libSDL2pp.git
cd libSDL2pp
git checkout 0.18.1
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
echo "libsdl2pp installed"

