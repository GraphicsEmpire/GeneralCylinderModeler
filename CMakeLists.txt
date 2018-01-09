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
include (${SWDEPS_ROOT_DIR}/cmake/nourbrain.cmake)

## build main source
# executable
add_executable(${PROJECT_NAME} src/main.cpp src/catmullromcurve.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC src/ src/linalg)
target_link_libraries(${PROJECT_NAME} glfw3)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
