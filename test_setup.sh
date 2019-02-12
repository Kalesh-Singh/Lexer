#!/bin/bash
sudo apt-get install libgtest-dev   # Install Google Test source files
sudo apt-get install cmake          # Install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make                           # Build google test

# Copy or symlink libgtest.a and libgtest_main.a
# to /usr/lib
sudo cp *.a /usr/lib