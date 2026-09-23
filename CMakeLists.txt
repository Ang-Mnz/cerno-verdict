cmake_minimum_required(VERSION 3.20)

project(cerno_verdict
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

# Application principale
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(cerno_verdict
	${SOURCES}
)

target_include_directories(cerno_verdict
	PRIVATE
		src
)

target_link_libraries(cerno_verdict
    PRIVATE
        ${OpenCV_LIBS}
)

# Tests
include(CTest)

enable_testing()

add_subdirectory(tests)
