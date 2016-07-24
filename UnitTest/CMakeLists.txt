set(SOURCES UnitTest.cpp
            TestR3.cpp
            TestComplex.cpp)

set(HEADERS TestR3.h
            TestComplex.h)

add_executable(UnitTest ${SOURCES} ${HEADERS})

target_link_libraries(UnitTest NovaType)
