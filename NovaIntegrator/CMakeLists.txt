set(SOURCES IntegrationRule.cpp
            GaussRule1D.cpp
            GaussRule2D_Tri.cpp
            GaussRule3D_Tet.cpp
            Integrator.cpp
            FixedPointIntegrator.cpp
            FixedPntIntegrator1D.cpp
            FixedPntIntegrator2D_Tri.cpp
            FixedPntIntegrator2D_Quad.cpp
            FixedPntIntegrator3D_Tet.cpp)

set(HEADERS IntegrationRule.h
            GaussRule1D.h
            GaussRule2D_Tri.h
            GaussRule3D_Tet.h
            Integrand.h
            Integrator.h
            FixedPointIntegrator.h
            FixedPntIntegrator1D.h
            FixedPntIntegrator2D_Tri.h
            FixedPntIntegrator2D_Quad.h
            FixedPntIntegrator3D_Tet.h)

add_library(NovaIntegrator ${SOURCES} ${HEADERS})

target_link_libraries(NovaIntegrator NovaMesh NovaType NovaDef)
