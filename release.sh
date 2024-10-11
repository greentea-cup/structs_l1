#!/bin/bash
X=$1
shift
cmake --build build/Release && ./build/Release/app$X $@
