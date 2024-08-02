#!/bin/bash
set -e

# Determine the number of CPU cores
NUM_CORES=$(nproc)

# Build and install Protobuf
cd third_party/protobuf-3.19.6

# Configure the build to include only C++ and Python
./configure --prefix=$(pwd)/install --disable-java --disable-javascript --disable-csharp --disable-ruby --disable-go --disable-php --disable-objectivec

# Build and install using all available CPU cores
make -j$NUM_CORES
make install
cd ../..

# Generate Protobuf files
third_party/protobuf-3.19.6/install/bin/protoc --cpp_out=src/ --proto_path=proto/ proto/message.proto
third_party/protobuf-3.19.6/install/bin/protoc --python_out=scripts/ --proto_path=proto/ proto/message.proto

# Build the project using all available CPU cores
mkdir -p build
cd build
cmake ..
make -j$NUM_CORES
