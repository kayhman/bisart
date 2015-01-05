cmake_minimum_required(VERSION 2.8.11)

project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(OLD_SRC "src/oldStyle/")
set(NEW_SRC "src/newStyle/")


# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(OpenGL)

# Tell CMake to create the oldStylex executable
add_executable(oldStyle ${OLD_SRC}/glWidget.cpp ${OLD_SRC}/window.cpp ${OLD_SRC}/main.cpp)

#add_executable(newStyle ${OLD_SRC}/glWidget.cpp ${OLD_SRC}/window.cpp ${OLD_SRC}/main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(oldStyle Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES})
