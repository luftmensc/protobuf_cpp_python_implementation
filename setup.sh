#!/bin/bash
set -e

# Determine the number of CPU cores
NUM_CORES=$(nproc)

mkdir -p third_party
if [ ! -d "third_party/protobuf-3.19.6" ]; then
    wget https://github.com/protocolbuffers/protobuf/releases/download/v3.19.6/protobuf-all-3.19.6.tar.gz -O third_party/protobuf-all-3.19.6.tar.gz
    tar -xzf third_party/protobuf-all-3.19.6.tar.gz -C third_party
    rm third_party/protobuf-all-3.19.6.tar.gz
fi

cd third_party/protobuf-3.19.6
./configure --prefix=$(pwd)/install --disable-java --disable-javascript --disable-csharp --disable-ruby --disable-go --disable-php --disable-objectivec

# Build and install using all available CPU cores
make -j$NUM_CORES
make install

# Wait for protoc installation
while [ ! -f "install/bin/protoc" ]; do
    echo "Waiting for protoc to be installed..."
    sleep 3
done

cd ../..

# Generate Protobuf files
third_party/protobuf-3.19.6/install/bin/protoc --cpp_out=src/ --proto_path=proto/ proto/message.proto
third_party/protobuf-3.19.6/install/bin/protoc --python_out=scripts/ --proto_path=proto/ proto/message.proto

# Build the project using all available CPU cores
mkdir -p build
cd build
cmake ..
make -j$NUM_CORES
