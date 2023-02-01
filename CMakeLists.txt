cmake_minimum_required(VERSION 3.24)
project(ex4_files C)

set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Add the source files to the project
add_executable(Ex4_ComputerStructure showBMP.c myutil.c myfunction1.c myfunction.c readBMP.c writeBMP.c)

# Specify the include directories for the OpenGL and GLUT libraries
target_include_directories(Ex4_ComputerStructure PRIVATE ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

# Link the OpenGL and GLUT libraries to the project
target_link_libraries(Ex4_ComputerStructure ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} -lm -lglut -lGL -lGLU -lX11 -lXmu -lXi -L/usr/X11R6/lib)

# Set the output directory for the executable
set_target_properties(Ex4_ComputerStructure PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
