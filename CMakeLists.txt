


cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(serialization)


enable_testing()



option(SERIALIZATION_EXTRA_ABSL
    "Link additional Abseil libraries required by some environments"
    OFF
)

set(SERIALIZATION_ABSL_LIBS)
 list(APPEND SERIALIZATION_ABSL_LIBS
        absl::strings
    )
if (SERIALIZATION_EXTRA_ABSL)
    list(APPEND SERIALIZATION_ABSL_LIBS
        absl::log
        absl::log_internal_check_op
    )
endif()






set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/app)


find_package(absl REQUIRED) #dependency for protobuf
find_package(Protobuf REQUIRED)









set(PROTO_FILES
    src/proto/server.proto
    src/proto/chat.proto
)


# imported with find_package
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
    ${PROTO_FILES}
)




#simply  for IDE to properly find headers
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
    {CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)


## Core library


add_library(serialization_core
    src/server/mockserver.cpp
    src/client/client.cpp
    src/networking/connection.cpp
    src/messages/messages.cpp
    src/messages/messageprinting.cpp
    ${PROTO_SRCS}
)

target_include_directories(serialization_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
    ${HEADER_FILES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(serialization_core
    PRIVATE
        protobuf::libprotobuf
        ${SERIALIZATION_ABSL_LIBS}



)




## main app


add_executable(serialization
    src/main.cpp    

)

target_link_libraries(serialization PRIVATE serialization_core)







# BINARY one allows searches inside build folder (not the .exe folder), the other, searches in the "code" folder
target_include_directories(serialization PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}

)






target_link_libraries(serialization
	PRIVATE
    protobuf::libprotobuf
        ${SERIALIZATION_ABSL_LIBS}



	
)



### Testing

add_subdirectory(tests)

