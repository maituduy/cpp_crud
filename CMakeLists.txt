cmake_minimum_required(VERSION 3.15)
project(cpp_CRUD)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

find_package(mysqlcppconn REQUIRED)
include_directories(${MYSQLCPPCONN_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(LIBS ${LIBS} ${MYSQLCPPCONN_LIBRARIES})

add_executable(cpp_CRUD main.cpp)
target_link_libraries(cpp_CRUD ${LIBS})