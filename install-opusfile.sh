#!/bin/bash
echo "Installing Opusfile"
git clone https://github.com/xiph/opusfile.git || echo "Error: git clone failed, check your internet connection"
cd opusfile || echo "Error: opusfile directory not found"
mkdir build || echo "Error: build directory could not be created or already exists" | exit 1
cd build || echo "Error: build directory not found" | exit 1
cmake -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON .. || echo "Error: cmake configuring failed" | exit 1
cmake --build . || echo "Error: cmake build failed" | exit 1
sudo cmake --install . || echo "Error: cmake install failed" | exit 1
echo "Opusfile installed"

