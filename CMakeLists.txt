cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("Nova EM")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") 

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")

SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -O2 -g")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

add_subdirectory(NovaDef)

include_directories(SYSTEM "NovaDef")

add_subdirectory(NovaType)

include_directories(SYSTEM "NovaType")

add_subdirectory(NovaMesh)

include_directories(SYSTEM "NovaMesh")

add_subdirectory(NovaBasis)

include_directories(SYSTEM "NovaBasis")

add_subdirectory(NovaTools)

include_directories(SYSTEM "NovaTools")

add_subdirectory(UnitTest)

add_executable(NovaEM main.cpp)

include_directories(SYSTEM "$HOME/tools/include")

link_directories(SYSTEM "$HOME/tools/lib")

target_link_libraries(NovaEM 
                      NovaDef
                      NovaType 
                      NovaMesh
                      NovaBasis)

