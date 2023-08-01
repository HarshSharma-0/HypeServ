cmake_minimum_required(VERSION 3.6.0)
project(server)
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/master
        ${PROJECT_SOURCE_DIR}/worker
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/src/*"
        "${PROJECT_SOURCE_DIR}/master/*"
        "${PROJECT_SOURCE_DIR}/worker/*"
)
add_definitions(-DGLES2)
add_executable(server ${SRCS})
