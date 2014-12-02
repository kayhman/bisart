cmake_minimum_required(VERSION 2.8.11)

project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(OpenGL)

# Tell CMake to create the helloworld executable
add_executable(helloworld src/glWidget.cpp src/window.cpp src/main.cpp src/qtlogo.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES})
