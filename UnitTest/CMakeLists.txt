set(SOURCES UnitTest.cpp
            TestR3.cpp
            TestComplex.cpp
            TestPatch.cpp
            TestBasis.cpp)

set(HEADERS TestR3.h
            TestComplex.h
            TestPatch.h
            TestBasis.h)

add_executable(UnitTest ${SOURCES} ${HEADERS})

target_link_libraries(UnitTest NovaType NovaMesh NovaDef NovaBasis)
