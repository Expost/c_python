cmake_minimum_required(VERSION 3.0.0)
project(c_python VERSION 0.1.0)

include(CTest)
enable_testing()


find_package(Python3 COMPONENTS Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})

include_directories(extern/pybind11/include)

add_executable(loader loader.cpp)
add_library(replaysvr SHARED  replaysvr.cpp)

set(CMAKE_CXX_FLAGS -std=c++11)

target_link_libraries(replaysvr PRIVATE ${Python3_LIBRARIES})
target_link_libraries(loader PRIVATE dl)

add_custom_command(TARGET replaysvr POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_BINARY_DIR}/libreplaysvr.so ${CMAKE_BINARY_DIR}/replaysvr.so
)

add_custom_command(TARGET replaysvr POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/logic.py ${CMAKE_BINARY_DIR}/logic.py
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
