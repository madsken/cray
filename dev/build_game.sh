#!/bin/bash

# Used to build the game and move it to root folder for hot reloading

cmake --build build --target game

cp build/libgame.so .
