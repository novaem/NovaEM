cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("Nova EM")

include_directories(SYSTEM "NovaType")

add_subdirectory(NovaType)

add_subdirectory(UnitTest)

add_executable(NovaEM main.cpp)

target_link_libraries(NovaEM NovaType)

