#!/bin/sh

cmake --preset release
cmake --build --preset release

./build/release/bin/nutflow videos/user1.mp4
