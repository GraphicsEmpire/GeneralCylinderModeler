## build script for gencylinder project
cmake_minimum_required(VERSION 3.2)

## project name
project(gencylinder)

## add dependencies
if (NOT DEFINED SWDEPS_ROOT_DIR)
  if(WIN32)
    set (SWDEPS_ROOT_DIR "C:/swdeps" CACHE FILEPATH "If swdeps is available, specify its path")
  endif(WIN32)

  if(UNIX)
    set (SWDEPS_ROOT_DIR "/swdeps" CACHE FILEPATH "If swdeps is available, specify its path")
  endif(UNIX)
endif()

## include swdeps
message("SWDEPS_ROOT_DIR = ${SWDEPS_ROOT_DIR}")
if (APPLE)
  set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
endif(APPLE)

include (${SWDEPS_ROOT_DIR}/cmake/nourbrain.cmake)

#--------------------------------------------------
# over-write binary output storage paths
#--------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

#--------------------------------------------------
# c++11 features
#--------------------------------------------------
set (CMAKE_CXX_STANDARD 11)

#--------------------------------------------------
# src files
#--------------------------------------------------
set (SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories(${SOURCE_ROOT})
add_subdirectory(src/linalg)
add_subdirectory(src/opengl)
add_subdirectory(src/utils)
##add_subdirectory(src/render)

#--------------------------------------------------
# final application
#--------------------------------------------------
add_subdirectory(src/application)
