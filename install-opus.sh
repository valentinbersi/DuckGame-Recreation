#!/bin/bash
echo "Installing Opus"
git clone https://github.com/xiph/opus.git
cd opus
git checkout v1.5.2
mkdir build
cd build
cmake -DCMAKE_C_FLAGS="-fPIC" -DCMAKE_CXX_FLAGS="-fPIC" ..
cmake --build .
sudo cmake --install .
echo "Opus installed"

