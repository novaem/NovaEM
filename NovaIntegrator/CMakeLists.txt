set(SOURCES IntegrationRule.cpp
            GaussRule1D.cpp
            GaussRule2D_Tri.cpp
            GaussRule3D_Tet.cpp
            Integrator.cpp
            FixedPointIntegrator.cpp
            FixedPntIntegrator1D.cpp
            FixedPntIntegrator2D_Tri.cpp
            FixedPntIntegrator2D_Quad.cpp
            FixedPntIntegrator3D_Tet.cpp
            FixedPntIntegrator3D_Hex.cpp
            AdaptiveIntegrator.cpp
            AdaptiveIntegrator1D.cpp
            AdaptiveIntegrator2D_Tri.cpp)

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
            FixedPntIntegrator3D_Tet.h
            FixedPntIntegrator3D_Hex.h
            AdaptiveIntegrator.h
            AdaptiveIntegrator1D.h
            AdaptiveIntegrator2D_Tri.h)

add_library(NovaIntegrator ${SOURCES} ${HEADERS})

target_link_libraries(NovaIntegrator NovaMesh NovaType NovaDef)
