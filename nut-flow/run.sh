#!/bin/sh

cmake --preset release
cmake --build --preset release

./build/release/bin/nutflow videos/user1.mp4
./build/release/bin/nutflow videos/user2.mp4
./build/release/bin/nutflow videos/user3.mp4
