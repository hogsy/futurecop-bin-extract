cmake_minimum_required(VERSION 3.10)
project(futurecop_tk C)

set(CMAKE_C_STANDARD 11)

set(PL_SUPPORT_OPENGL OFF CACHE BOOL "Graphics OpenGL API support")
add_subdirectory(platform/platform)

include_directories(platform/platform/include/)

add_executable(futurecop_tk main.c)
target_link_libraries(futurecop_tk platform)