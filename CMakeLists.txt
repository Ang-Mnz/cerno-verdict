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
	src/utils/bit_utils.cpp
	src/hardware/register8.cpp
	src/hardware/gpio_pin.cpp
	src/communication/uart.cpp
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

# Tests bit utils
add_executable(bit_utils_test
	tests/bit_utils_test.cpp
	src/utils/bit_utils.cpp
)

target_include_directories(bit_utils_test
	PRIVATE
		src
)

# Tests register8
add_executable(register8_test
	tests/register8_test.cpp
	src/hardware/register8.cpp
	src/utils/bit_utils.cpp
)

target_include_directories(register8_test
	PRIVATE
		src
)

# Tests gpio_pin
add_executable(gpio_pin_test
	tests/gpio_pin_test.cpp
	src/hardware/gpio_pin.cpp
)

target_include_directories(gpio_pin_test
	PRIVATE
		src
)

# Tests UART
add_executable(uart_test
	tests/uart_test.cpp
	src/communication/uart.cpp
	src/communication/circular_buffer.cpp
)

target_include_directories(uart_test
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

add_test(
	NAME bit_utils_test
	COMMAND bit_utils_test
)

add_test(
	NAME register8_test
	COMMAND register8_test
)

add_test(
	NAME gpio_pin_test
	COMMAND gpio_pin_test
)

add_test(
	NAME uart_test
	COMMAND uart_test
)
