# Protobuf Example Project

This project demonstrates how to use Protocol Buffers with C++ and Python. It includes examples for both sending and receiving Protobuf messages using Boost.Asio and asyncio.

**TESTED WITH CLEAN CLONE AND BUILD WITH ./setup.sh**

## Directory Structure

```plaintext
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
```

## Setup and Build

1. **Run the setup script:**

   ```./setup.sh```

   after the installation, if you made changes in cpp and just want to build:

   ```cd build && cmake .. && make```
   

## Running the Examples

### C++ Example

1. **Run the receiver:**

   ```./build/communication receiver```

2. **Run the sender:**

   ```./build/communication sender```

### Python Example

1. **Run the receiver:**

   ```python scripts/communication.py receiver```

2. **Run the sender:**

   ```python scripts/communication.py sender```

   **WARNING:** You need to run receiver before sender.

   **USAGE TYPES:** 4 possibility for usage types:
   - Receiver with python, sender with python
   - Receiver with python, sender with c++
   - Receiver with c++, sender with python
   - Receiver with c++, sender with c++
   
   This ensures the cross compatibility of the Protobuf messages between C++ and Python.

## Dependencies

- Protocol Buffers (https://developers.google.com/protocol-buffers)
- Boost (https://www.boost.org/)
- CMake (https://cmake.org/)

Ensure that you have installed the required dependencies and set up your environment correctly.

### Cloning and Setting Up the Repository

1. **Clone the repository:**

```
   git clone https://github.com/luftmensc/protobuf_cpp_python_implementation.git
   cd protobuf_cpp_python_implementation
```

2. **Run the setup script:**

   ```./setup.sh```

3. **Run the examples as described in the README.

