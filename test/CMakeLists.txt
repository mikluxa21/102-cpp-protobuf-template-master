include_directories(${GTEST_INCLUDE_DIRS})
find_package(GTest REQUIRED)
set(TEST_NAME proto_test)

add_executable(${TEST_NAME}
	Test_DelimitedMessagesStreamParser.cpp
 	Test_Helpers.cpp
)
add_test(NAME ${TEST_NAME}
	COMMAND ${TEST_NAME}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${TEST_NAME}
			gtest
			gtest_main
			pthread
			proto
			${Protobuf_LIBRARIES}
)
