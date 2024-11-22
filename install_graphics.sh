#!/bin/bash
echo "Installing graphics, sudo password may be required."
sudo apt update
sudo apt install -y qtbase5-dev qtbase5-dev-tools qttools5-dev qttools5-dev-tools libqt5core5a libqt5gui5 libqt5widgets5
sudo apt upgrade -y
echo "Graphics installed."
