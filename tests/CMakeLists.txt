# Tests UART
add_executable(uart_test
	communication/uart_test.cpp
	../src/communication/uart.cpp
)

target_include_directories(uart_test
	PRIVATE
		../src
)

# CTests

add_test(
	NAME uart_test
	COMMAND uart_test
)
