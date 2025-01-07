#!/bin/bash
X=$1
shift
cmake --build build/Release -t app$X && ./build/Release/app$X $@
