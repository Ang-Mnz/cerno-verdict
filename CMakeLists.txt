cmake_minimum_required(VERSION 3.20)

project(cerno_verdict
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

# Télécharger automatiquement: cpp-httplib
include(FetchContent)

FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.18.3
)

FetchContent_MakeAvailable(httplib)

# Application principale
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/praetorium/*.cpp"
)

add_executable(cerno_verdict
    ${SOURCES}
)

target_include_directories(cerno_verdict
    PRIVATE
        praetorium
)

target_link_libraries(cerno_verdict
    PRIVATE
        ${OpenCV_LIBS}
		httplib::httplib
)

# Tests
include(CTest)

enable_testing()

add_subdirectory(tests)
