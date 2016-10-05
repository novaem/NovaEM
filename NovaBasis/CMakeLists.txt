set(SOURCES Basis.cpp) 

set(HEADERS Basis.h)

add_library(NovaBasis ${SOURCES} ${HEADERS})

target_link_libraries(NovaBasis NovaMesh NovaType NovaDef)
