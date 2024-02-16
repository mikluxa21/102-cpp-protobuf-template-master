#add_executable(message_test Test_DelimitedMessagesStreamParser.cpp Test_Helpers.cpp)
#target_link_libraries( message_test gtest gtest_main pthread proto_lib)

set(TEST_NAME proto_test)
INCLUDE_DIRECTORIES(${Protobuf_INCLUDE_DIRS})
add_executable(${TEST_NAME}
	Test_DelimitedMessagesStreamParser.cpp
 	Test_Helpers.cpp
  )
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TEST_NAME} gtest gtest_main pthread proto ${Protobuf_LIBRARIES})
