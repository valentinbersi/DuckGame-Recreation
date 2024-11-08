#!/bin/bash
echo "Installing dependencies..."
apt update
apt install -y libsdl2-2.0-0 libsdl2-dev libsdl2-doc libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-net-2.0-0 libsdl2-net-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev libsdl2-gfx-1.0-0 libsdl2-gfx-dev
apt install -y qtbase5-dev qtbase5-dev-tools qttools5-dev qttools5-dev-tools libqt5core5t64 libqt5gui5t64 libqt5widgets5t64
apt upgrade -y
echo "Dependencies installed."
