set(SOURCES R3.cpp
            NovaComplex.cpp)

set(HEADERS R3.h
            NovaComplex.h)

add_library(NovaType ${SOURCES} ${HEADERS})

target_link_libraries(NovaType NovaDef)
