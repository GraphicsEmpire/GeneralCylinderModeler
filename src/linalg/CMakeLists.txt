#cmake file to compile nbLinearAlgebra library
#########################################################
## add source files
#########################################################
file(GLOB SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
        )

file(GLOB HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        )


#########################################################
#Linking
#########################################################
add_library(nbLinearAlgebra SHARED ${SOURCE_FILES} ${HEADER_FILES})
add_library(nbLinearAlgebra_static STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Visual Studio Folder
#SET_PROPERTY(TARGET nbLinearAlgebra PROPERTY FOLDER "CoreLibrary")

# Install Folder
install (TARGETS nbLinearAlgebra DESTINATION lib)
install (TARGETS nbLinearAlgebra_static DESTINATION lib)
install (FILES ${HEADER_FILES} DESTINATION include/nb/linalg)
