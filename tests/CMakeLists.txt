
find_package(doctest CONFIG REQUIRED)



add_executable( serialization_testing
    tests_main.cpp
    server_tests.cpp
    connection_tests.cpp
)

target_link_libraries(serialization_testing
    PRIVATE
        serialization_core
	doctest::doctest
)

add_test(
    NAME serialization_testing
    COMMAND serialization_testing
)



