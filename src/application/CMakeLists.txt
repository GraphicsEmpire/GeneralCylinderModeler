# executable
add_executable(${PROJECT_NAME} catmullromcurverender.cpp catmullromcurve.cpp main.cpp)
target_link_libraries(${PROJECT_NAME} glfw3)
install(TARGETS ${PROJECT_NAME} DESTINATION bin) 
