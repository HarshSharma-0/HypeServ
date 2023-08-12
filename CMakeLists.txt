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
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
add_executable(server ${SRCS})
