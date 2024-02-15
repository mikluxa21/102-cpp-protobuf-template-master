#set(PROTOBUF_TARGET_NAME Message)

find_package(Protobuf REQUIRED)

#include_directories(${PROTOBUF_INCLUDE_DIRS})

#set(PROTO_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS message.proto)

add_library(proto_lib OBJECT ${PROTO_SRCS} ${PROTO_HDRS})




#${PROTOBUF_TARGET_NAME}
#add_custom_command(
#    TARGET Message POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#            ${PROTO_SRCS} ${PROTO_HDRS}
#            ${PROTO_OUTPUT_DIR}
#)

#target_link_libraries(${PROTOBUF_TARGET_NAME} PUBLIC protobuf::libprotobuf)
