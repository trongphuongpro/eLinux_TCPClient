cmake_minimum_required(VERSION 3.0)

#-----------------------------------------------------------------------------#
find_package(Threads REQUIRED)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
#-----------------------------------------------------------------------------#

set(TARGET testbench)

add_executable(${TARGET} test.cpp ../src/tcpclient.cpp)

target_include_directories(${TARGET} PUBLIC ../include)

#-----------------------------------------------------------------------------#
target_compile_options(${TARGET} PUBLIC -std=gnu++11
										-Wall
										-Werror
										-O2
)
#-----------------------------------------------------------------------------#
install(TARGETS ${TARGET} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)