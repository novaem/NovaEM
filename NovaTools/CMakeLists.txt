set(SOURCES RuleGenerator.cpp)

set(HEADERS RuleGenerator.h)

add_executable(NovaTools ${SOURCES} ${HEADERS})

target_link_libraries(NovaTools
                      NovaMesh
                      NovaDef
                      NovaBasis
                      gmpxx
                      gmp)
