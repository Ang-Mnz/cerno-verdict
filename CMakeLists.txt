cmake_minimum_required(VERSION 3.20)

project(cerno_verdict
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	src/main.cpp
	src/memory/memory.cpp
)

add_executable(cerno_verdict
	${SOURCES}
)

target_include_directories(cerno_verdict
	PRIVATE
		src
)
