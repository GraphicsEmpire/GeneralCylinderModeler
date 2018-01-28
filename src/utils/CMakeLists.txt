#cmake file to compile nbUtils library
#########################################################
## enable pthread
#########################################################
find_package(Threads)


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
add_library(nbUtils SHARED ${HEADER_FILES} ${SOURCE_FILES})
add_dependencies(nbUtils nbLinearAlgebra_static)

add_library(nbUtils_static STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_dependencies(nbUtils_static nbLinearAlgebra_static)

target_link_libraries(nbUtils nbLinearAlgebra_static ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(nbUtils_static nbLinearAlgebra_static ${CMAKE_THREAD_LIBS_INIT})


# Visual Studio Folder
#SET_PROPERTY(TARGET nbUtils PROPERTY FOLDER "CoreLibrary")

# Install Folder
install (TARGETS nbUtils DESTINATION lib)
install (TARGETS nbUtils_static DESTINATION lib)
install (FILES ${HEADER_FILES} DESTINATION include/nb/utils)
