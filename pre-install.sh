#!/bin/bash
echo "Installing dependencies, sudo password may be required."
echo | sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential cmake g++ nasm clang clang-format cppcheck pkg-config alsa-base alsa-utils libasound2-dev qtbase5-dev qtbase5-dev-tools qttools5-dev qttools5-dev-tools libqt5core5a libqt5gui5 libqt5widgets5 flex bison javacc libopus0 libopus-dev opus-tools libogg0 libogg-dev vorbis-tools doxygen libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev libfreetype6-dev libssl-dev libxmp-dev libfluidsynth-dev libwavpack-dev libjpeg-dev gpp cpp gcc-11 g++-11
mkdir dependencies || echo "Error: dependencies directory could not be created or already exists" | exit 1
cd dependencies || echo "Error: dependencies directory not found" | exit 1
../install-sdl.sh || echo "Error: SDL could not be installed" | exit 1
../install-sdl-image.sh || echo "Error: SDL_image could not be installed" | exit 1
../install-opus.sh || echo "Error: Opus could not be installed" | exit 1
../install-opusfile.sh || echo "Error: Opusfile could not be installed" | exit 1
sudo cp /usr/local/lib/cmake/opusfile/OpusFileTargets.cmake /usr/local/lib/cmake/opusfile/opusfileTargets.cmake
sudo cp /usr/local/lib/cmake/opusfile/OpusFileTargets-noconfig.cmake /usr/local/lib/cmake/opusfile/opusfileTargets-noconfig.cmake
../install-sdl-mixer.sh || echo "Error: SDL_mixer could not be installed" | exit 1
../install-sdl-ttf.sh || echo "Error: SDL_ttf could not be installed" | exit 1
../install-libsdl2pp.sh || echo "Error: libsdl2pp could not be installed" | exit 1
cd ..
rm -r dependencies || echo "Error: dependencies directory could not be removed"
sudo apt upgrade -y
echo "Pre dependencies installed"
