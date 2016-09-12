set(SOURCES Node.cpp
            Element.cpp
            Element2D.cpp
            Element3D.cpp)

set(HEADERS Node.h
            Element.h
            Element2D.h
            Element3D.h)

add_library(NovaMesh ${SOURCES} ${HEADERS})
