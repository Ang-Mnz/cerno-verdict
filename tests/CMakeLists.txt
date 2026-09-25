# Tests UART
add_executable(uart_test
    communication/uart_test.cpp
    ../praetorium/communication/uart.cpp
)

target_include_directories(uart_test
    PRIVATE
        ../praetorium
)

# Tests MotionManager
add_executable(motion_manager_test
    application/motion_manager_test.cpp
    ../praetorium/application/motion_manager/motion_manager.cpp
    ../praetorium/application/motion_manager/motion_event.cpp
    ../praetorium/application/storage/events_storage.cpp
)

target_include_directories(motion_manager_test
    PRIVATE
        ../praetorium
)

target_link_libraries(motion_manager_test
    PRIVATE
        ${OpenCV_LIBS}
)

# Tests EventStorage
add_executable(event_storage_test
    application/event_storage_test.cpp
    ../praetorium/application/motion_manager/motion_event.cpp
    ../praetorium/application/storage/events_storage.cpp
)

target_include_directories(event_storage_test
    PRIVATE
        ../praetorium
)

target_link_libraries(event_storage_test
    PRIVATE
        ${OpenCV_LIBS}
)

# CTests

add_test(
    NAME uart_test
    COMMAND uart_test
)

add_test(
    NAME motion_manager_test
    COMMAND motion_manager_test
)

add_test(
    NAME event_storage_test
    COMMAND event_storage_test
)
