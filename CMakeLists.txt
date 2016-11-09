cmake_minimum_required(VERSION 3.6)
project(Snake)

add_library(snake STATIC snake.cpp)
add_executable(snake.exe main.cpp)
target_link_libraries(snake)