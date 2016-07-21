cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("Nova EM")

add_executable(NovaEM main.cpp)

add_subdirectory(NovaType)

target_link_libraries(NovaEM NovaType)

