# cmake to build render module
#########################################################
## add source files
#########################################################
file(GLOB SOURCE_FILES
     sgmodel.cpp
        )

file(GLOB HEADER_FILES
    sgrenderinterface.h
    sgmodel.h
    )
#########################################################
#Linking
#########################################################
add_library(nbRender SHARED ${HEADER_FILES} ${SOURCE_FILES})
add_dependencies(nbRender nbUtils_static nbLinearAlgebra_static)

add_library(nbRender_static STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_dependencies(nbRender_static nbUtils_static nbLinearAlgebra_static)

target_link_libraries(nbRender nbUtils_static nbLinearAlgebra_static)
target_link_libraries(nbRender_static nbUtils_static nbLinearAlgebra_static)

# Install Folder
install (TARGETS nbRender DESTINATION lib)
install (TARGETS nbRender_static DESTINATION lib)
install (FILES ${HEADER_FILES} DESTINATION include/nb/render)
