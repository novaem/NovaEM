set(SOURCES IntegrationRule.cpp
            GaussRule3D_Tet.cpp)

set(HEADERS IntegrationRule.h
            GaussRule3D_Tet.h)

add_library(NovaIntegrator ${SOURCES} ${HEADERS})

target_link_libraries(NovaIntegrator NovaMesh NovaType NovaDef)
