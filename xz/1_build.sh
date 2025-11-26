#!/bin/bash

rerun_cmake=$1

mkdir -p build
cd build

export CC="ccache gcc"
export CXX="ccache g++"

if [ "$rerun_cmake" == "1" ]; then
	cd ..
	rm -rf build
	mkdir build
	cd build
	cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G"Ninja"
fi

ninja -j$(nproc)
