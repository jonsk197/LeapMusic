add_library (Graphics Graphics.cpp)
target_link_libraries (Graphics ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})