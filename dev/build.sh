#!/bin/bash

# Used to build the game and engine (if they have not been built yet)

mkdir -p build
cd build
cmake ..
make -j$(nproc)

cp libgame.so cray ../
