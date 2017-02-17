#!/bin/sh
if [ ! -e build ]; then
	mkdir build
fi
cd build
cmake ../
make
cp LuaSample ../
cd ../
