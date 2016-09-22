set(SOURCES Node.cpp
            Patch.cpp
            Patch2D.cpp
            Patch3D.cpp
            Triangle.cpp
            Quad.cpp)

set(HEADERS Node.h
            Patch.h
            Patch2D.h
            Patch3D.h
            Triangle.h
            Quad.h)

add_library(NovaMesh ${SOURCES} ${HEADERS})

target_link_libraries(NovaMesh NovaType NovaDef)
