cmake_minimum_required(VERSION 3.16)
project(OpenCVProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV and Qt6 packages
find_package(OpenCV REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Source files
set(SOURCES
  main.cpp
  MainWindow.cpp
  Canvas.cpp
  Pixel.cpp
  include/MainWindow.h  # Ensure this is included for MOC
  include/Canvas.h
)

# Add executable
add_executable(OpenCVProject ${SOURCES})

# Add your include directory
target_include_directories(OpenCVProject PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link OpenCV and Qt6 libraries
target_link_libraries(OpenCVProject PRIVATE ${OpenCV_LIBS} Qt6::Widgets)

# Ensure Qt's MOC is run on the header files
qt6_wrap_cpp(MOC_SOURCES include/MainWindow.h include/Canvas.h)
target_sources(OpenCVProject PRIVATE ${MOC_SOURCES})
