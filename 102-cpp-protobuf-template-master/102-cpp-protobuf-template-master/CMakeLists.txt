cmake_minimum_required(VERSION 3.16.3)
cmake_policy(SET CMP0016 NEW)

project(protobuf_parser VERSION 1.0.0 DESCRIPTION "Разбор потока length-prefixed Protobuf сообщений на C++")

include_directories(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(src/protobuf)
add_subdirectory(test)

enable_testing()
