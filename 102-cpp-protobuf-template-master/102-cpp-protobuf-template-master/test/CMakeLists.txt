cmake_minimum_required(VERSION 3.16)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(Message)
add_executable(Example Test_Helpers.cpp)
target_link_libraries(Example
    Message
    gtest_main
    pthread
    )
add_test(
    NAME Example
    COMMAND Example
    )
