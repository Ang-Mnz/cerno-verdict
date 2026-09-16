# Tests memory
add_executable(memory_test
	memory/memory_test.cpp
	../src/memory/memory.cpp
)

target_include_directories(memory_test
	PRIVATE
		../src
)

# Tests circular buffer
add_executable(circular_buffer_test
	communication/circular_buffer_test.cpp
	../src/communication/circular_buffer.cpp
)

target_include_directories(circular_buffer_test
	PRIVATE
		../src
)

# Tests bit utils
add_executable(bit_utils_test
	utils/bit_utils_test.cpp
	../src/utils/bit_utils.cpp
)

target_include_directories(bit_utils_test
	PRIVATE
		../src
)

# Tests register8
add_executable(register8_test
	hardware/register8_test.cpp
	../src/hardware/register8.cpp
	../src/utils/bit_utils.cpp
)

target_include_directories(register8_test
	PRIVATE
		../src
)

# Tests gpio pin
add_executable(gpio_pin_test
	hardware/gpio_pin_test.cpp
	../src/hardware/gpio_pin.cpp
)

target_include_directories(gpio_pin_test
	PRIVATE
		../src
)

# Tests UART
add_executable(uart_test
	communication/uart_test.cpp
	../src/communication/uart.cpp
	../src/communication/circular_buffer.cpp
)

target_include_directories(uart_test
	PRIVATE
		../src
)

# CTests
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
