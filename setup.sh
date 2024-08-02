#!/bin/bash
set -e

# Determine the number of CPU cores
NUM_CORES=$(nproc)

# Create third_party directory if it doesn't exist
mkdir -p third_party

# Download and extract Protobuf if it doesn't exist
if [ ! -d "third_party/protobuf-3.19.6" ]; then
    wget https://github.com/protocolbuffers/protobuf/releases/download/v3.19.6/protobuf-all-3.19.6.tar.gz -O third_party/protobuf-all-3.19.6.tar.gz
    tar -xzf third_party/protobuf-all-3.19.6.tar.gz -C third_party
fi

# Build and install Protobuf
cd third_party/protobuf-3.19.6

# Configure the build to include only C++ and Python
./configure --prefix=$(pwd)/install --disable-java --disable-javascript --disable-csharp --disable-ruby --disable-go --disable-php --disable-objectivec

# Build and install using all available CPU cores
make -j$NUM_CORES
make install

# Verify protoc installation
if [ ! -f "install/bin/protoc" ]; then
    echo "Error: protoc was not installed correctly."
    exit 1
fi

cd ../..

# Generate Protobuf files
third_party/protobuf-3.19.6/install/bin/protoc --cpp_out=src/ --proto_path=proto/ proto/message.proto
third_party/protobuf-3.19.6/install/bin/protoc --python_out=scripts/ --proto_path=proto/ proto/message.proto

# Build the project using all available CPU cores
mkdir -p build
cd build
cmake ..
make -j$NUM_CORES
