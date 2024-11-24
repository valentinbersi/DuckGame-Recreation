#!/bin/bash
echo "Installing Opusfile"
git clone https://github.com/xiph/opusfile.git
cd opusfile
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .
sudo cmake --install .
echo "Opusfile installed"

