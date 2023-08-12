cmake_minimum_required(VERSION 3.6.0)
project(server)
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/SERVER_HEAD
        ${PROJECT_SOURCE_DIR}/SERVER_WORKER
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/src/*"
        "${PROJECT_SOURCE_DIR}/SERVER_HEAD/*"
        "${PROJECT_SOURCE_DIR}/SERVER_WORKER/*"
)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Check for C++20 support
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
    message(STATUS "Your compiler does not support C++20, falling back to C++17.")
    set(CMAKE_CXX_STANDARD 17)
else()
    message(STATUS "Your compiler support C++20, using C++20")
    set(CMAKE_CXX_STANDARD 20)
endif()

add_executable(server ${SRCS})
