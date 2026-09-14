cmake_minimum_required(VERSION 3.20)

project(cerno_verdict
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Application principale
set(SOURCES
	src/main.cpp
	src/memory/memory.cpp
	src/communication/circular_buffer.cpp
)

add_executable(cerno_verdict
	${SOURCES}
)

target_include_directories(cerno_verdict
	PRIVATE
		src
)

# Tests memory
add_executable(memory_test
	tests/memory_test.cpp
	src/memory/memory.cpp
)

target_include_directories(memory_test
	PRIVATE
		src
)

# Tests circular buffer
add_executable(circular_buffer_test
	tests/circular_buffer_test.cpp
	src/communication/circular_buffer.cpp
)

target_include_directories(circular_buffer_test
	PRIVATE
		src
)

# CTests
include(CTest)

enable_testing()

add_test(
	NAME memory_test
	COMMAND memory_test
)

add_test(
	NAME circular_buffer_test
	COMMAND circular_buffer_test
)
