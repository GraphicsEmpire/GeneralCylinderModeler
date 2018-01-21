#cmake file to compile nbOpenGLBackend lib
cmake_minimum_required(VERSION 3.2)

#########################################################
## other include files
#########################################################
include_directories(..
                    ${LODEPNG_DIR})


#########################################################
## add source files
#########################################################
file(GLOB SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
        ${LODEPNG_DIR}/lodepng.cpp
        )

file(GLOB HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${LODEPNG_DIR}/lodepng.h
        )

#########################################################
#Linking
#########################################################
add_library(nbOpenGLBackend SHARED ${HEADER_FILES} ${SOURCE_FILES} glrenderengine.h glrenderengine.cpp)
add_dependencies(nbOpenGLBackend nbLinearAlgebra_static)

add_library(nbOpenGLBackend_static STATIC ${HEADER_FILES} ${SOURCE_FILES} glrenderengine.h glrenderengine.cpp)
add_dependencies(nbOpenGLBackend_static nbLinearAlgebra_static)

target_link_libraries(nbOpenGLBackend glbinding nbUtils_static nbLinearAlgebra_static)
target_link_libraries(nbOpenGLBackend_static glbinding nbUtils_static nbLinearAlgebra_static)


# Visual Studio Folder
#SET_PROPERTY(TARGET nbOpenGLBackend PROPERTY FOLDER "CoreLibrary")

# Install Folder
install (TARGETS nbOpenGLBackend DESTINATION lib)
install (TARGETS nbOpenGLBackend_static DESTINATION lib)
install (FILES ${HEADER_FILES} DESTINATION include/nb/opengl)
