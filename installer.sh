./pre-install.sh || echo "Error: Pre-install failed" | exit 1
mkdir build
cd build || echo "Error: build directory could not be created" | exit 1
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./DuckGameTests || echo "Error: Tests failed, game won't be installed." | exit 1
sudo cmake --install .
sudo ldconfig
