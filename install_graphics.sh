#!/bin/bash
echo "Installing graphics, sudo password may be required."
sudo apt update
sudo apt install -y libsdl2-2.0-0 libsdl2-dev libsdl2-doc libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-net-2.0-0 libsdl2-net-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev libsdl2-gfx-1.0-0 libsdl2-gfx-dev qtbase5-dev qtbase5-dev-tools qttools5-dev qttools5-dev-tools libqt5core5a libqt5gui5 libqt5widgets5
sudo apt upgrade -y
echo "Graphics installed."
