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
|-- scripts/
|   |-- communication.py
|   |-- message_pb2.py
|-- third_party/
|   |-- (Protobuf source will be downloaded here)
|-- CMakeLists.txt
|-- README.md
|-- setup.sh
|-- .gitignore

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

   python scripts/communication.py receiver

2. **Run the sender:**

   python scripts/communication.py sender

## Dependencies

- Protocol Buffers (https://developers.google.com/protocol-buffers)
- Boost (https://www.boost.org/)
- CMake (https://cmake.org/)

Ensure that you have installed the required dependencies and set up your environment correctly.

### Cloning and Setting Up the Repository

1. **Clone the repository:**

   git clone <repository_url>
   cd protobuf_cpp_python_implementation

2. **Run the setup script:**

   ./setup.sh

3. **Run the examples as described in the README.

