To build only the C++ and Python parts of the Protobuf library, you can configure the Protobuf build to exclude the unnecessary components. The Protobuf build system allows you to specify which languages to build.

Here's how you can modify the `setup.sh` script to build only the C++ and Python components:

### Updated setup.sh Script

```sh
#!/bin/bash
set -e

# Build and install Protobuf
cd third_party/protobuf-3.19.6

# Configure the build to include only C++ and Python
./configure --prefix=$(pwd)/install --disable-java --disable-javascript --disable-csharp --disable-ruby --disable-go --disable-php --disable-objectivec

# Build and install
make
make install
cd ../..

# Generate Protobuf files
third_party/protobuf-3.19.6/install/bin/protoc --cpp_out=src/ --proto_path=proto/ proto/message.proto
third_party/protobuf-3.19.6/install/bin/protoc --python_out=python/ --proto_path=proto/ proto/message.proto

# Build the project
mkdir -p build
cd build
cmake ..
make
```

### Explanation

1. **Configure the Protobuf Build**: The `./configure` script accepts options to disable certain language bindings. The options used here disable Java, JavaScript, C#, Ruby, Go, PHP, and Objective-C, leaving only C++ and Python enabled.
2. **Generate Protobuf Files**: The `protoc` command generates the necessary C++ and Python files from the `.proto` file.
3. **Build the Project**: The standard `cmake` and `make` commands are used to build the project.

### Complete README.md

# Protobuf Example Project

This project demonstrates how to use Protocol Buffers with C++ and Python. It includes examples for both sending and receiving Protobuf messages using Boost.Asio and asyncio.

## Directory Structure

protobuf/
|-- build/
|-- include/
|   |-- message.pb.h
|-- proto/
|   |-- message.proto
|-- src/
|   |-- communication.cpp
|   |-- message.pb.cc
|-- python/
|   |-- communication.py
|   |-- message_pb2.py
|-- third_party/
|   |-- protobuf-3.19.6/
|-- CMakeLists.txt
|-- README.md
|-- setup.sh

## Setup and Build

1. **Run the setup script:**

   ./setup.sh

## Running the Examples

### C++ Example

1. **Run the receiver:**

   ./build/communication receiver

2. **Run the sender:**

   ./build/communication sender

### Python Example

1. **Run the receiver:**

   python python/communication.py receiver

2. **Run the sender:**

   python python/communication.py sender

## Dependencies

- Protocol Buffers (https://developers.google.com/protocol-buffers)
- Boost (https://www.boost.org/)
- CMake (https://cmake.org/)

Ensure that you have installed the required dependencies and set up your environment correctly.

### Cloning and Setting Up the Repository

1. **Clone the repository:**

   git clone <repository_url>
   cd protobuf

2. **Run the setup script:**

   ./setup.sh

3. **Run the examples as described in the README.**

By following these instructions, the project will be organized, and the setup script will only build the necessary components for C++ and Python, reducing the build time.