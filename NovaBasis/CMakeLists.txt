set(SOURCES Basis.cpp
            DivBasisTri.cpp
            DivBasisQuad.cpp
            DivBasisTet.cpp
            DivBasisHex.cpp)

set(HEADERS Basis.h
            DivBasisTri.h
            DivBasisQuad.h
            DivBasisTet.h
            DivBasisHex.h)

add_library(NovaBasis ${SOURCES} ${HEADERS})

target_link_libraries(NovaBasis NovaMesh NovaType NovaDef)
