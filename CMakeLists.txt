cmake_minimum_required(VERSION 3.10)
project(ProtobufExample)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include Protobuf
add_subdirectory(third_party/protobuf-3.19.6/cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${protobuf_SOURCE_DIR}/src)
include_directories(${protobuf_BINARY_DIR})

# Boost
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# Add source files
add_executable(communication
    src/communication.cpp
    src/message.pb.cc
)

target_link_libraries(communication
    protobuf::libprotobuf
    ${Boost_LIBRARIES}
    pthread
)
