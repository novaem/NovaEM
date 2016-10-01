set(SOURCES Node.cpp
            Patch.cpp
            Patch2D.cpp
            Patch3D.cpp
            Triangle.cpp
            Tet.cpp
            Quad.cpp
            Hex.cpp)

set(HEADERS Node.h
            Patch.h
            Patch2D.h
            Patch3D.h
            Triangle.h
            Tet.h
            Quad.h
            Hex.h)

add_library(NovaMesh ${SOURCES} ${HEADERS})

target_link_libraries(NovaMesh NovaType NovaDef)
