# Protobuf Example Project

This project demonstrates how to use Protocol Buffers with C++ and Python. It includes examples for both sending and receiving Protobuf messages using Boost.Asio and asyncio.

**TESTED WITH CLEAN CLONE AND BUILD WITH ./setup.sh**

## Cloning and Setting Up the Repository

1. **Clone the repository:**

```
   git clone https://github.com/luftmensc/protobuf_cpp_python_implementation.git
   cd protobuf_cpp_python_implementation
```

2. **Run the setup script:**

   ```./setup.sh```

3. **Run the examples as described in the Running the Examples section.**

## Directory Structure

```plaintext
protobuf/
|-- build/
|-- proto/
|   |-- message.proto
|-- src/
|   |-- communication.cpp
|   |-- message.pb.cc
    |-- message.pb.h
|-- scripts/
|   |-- communication.py
|   |-- message_pb2.py
|-- third_party/
|   |-- (Protobuf source will be downloaded here)
|-- tests/
    |-- test.cpp
|-- CMakeLists.txt
|-- README.md
|-- setup.sh
|-- .gitignore
```

## Setup and Build

1. **Run the setup script:**

   It takes around 2-3 minutes to download and build the Protobuf library.

   ```./setup.sh```

   after the installation, if you made changes in cpp and just want to build:

   ```cd build && cmake .. && make```


## Running the Examples

### Test Example

1. **Run the test:**

   ```./build/test_protobuf```

This test sends and receives a Protobuf message using C++ with Boost.Asio and threads. It creates two threads: one for sending and one for receiving. The sender thread sends data every 1 microsecond (1 MHz) for 10 seconds. The receiver thread receives the data and prints the received Person struct's ID.

To pass the test, the sender count must be equal to the receiver count, which is displayed at the end of the test and printed to the console.


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



