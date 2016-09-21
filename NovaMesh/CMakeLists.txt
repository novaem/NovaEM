set(SOURCES Node.cpp
            Patch.cpp
            Patch2D.cpp
            Element3D.cpp
            Triangle.cpp)

set(HEADERS Node.h
            Patch.h
            Patch2D.h
            Element3D.h
            Triangle.h)

add_library(NovaMesh ${SOURCES} ${HEADERS})
