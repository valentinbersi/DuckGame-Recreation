#!/bin/bash
echo "Installing Opus"
git clone https://github.com/xiph/opus.git || echo "Error: git clone failed, check your internet connection"
cd opus || echo "Error: opus directory not found"
git checkout v1.5.2
mkdir build || echo "Error: build directory could not be created or already exists" | exit 1
cd build || echo "Error: build directory not found" | exit 1
cmake -DCMAKE_C_FLAGS="-fPIC" -DCMAKE_CXX_FLAGS="-fPIC" .. || echo "Error: cmake configuring failed" | exit 1
cmake --build . || echo "Error: cmake build failed" | exit 1
sudo cmake --install . || echo "Error: cmake install failed" | exit 1
echo "Opus installed"

