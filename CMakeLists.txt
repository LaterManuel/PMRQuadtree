cmake_minimum_required(VERSION 3.10)
project(ShapeFileExample)

# Añadir la ruta de vcpkg a CMake
set(CMAKE_TOOLCHAIN_FILE "C:/Addons/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Usar vcpkg
include(CMakePrintHelpers)
cmake_print_variables(CMAKE_TOOLCHAIN_FILE)

# Encontrar la biblioteca shapelib
find_package(shapelib CONFIG REQUIRED)

# Verificar si la biblioteca fue encontrada
if(shapelib_FOUND)
    message(STATUS "shapelib found")
else()
    message(FATAL_ERROR "shapelib not found")
endif()

# Añadir el ejecutable
add_executable(ShapeFileExample main_v2.cpp)

# Vincular la biblioteca shapelib al ejecutable
target_link_libraries(ShapeFileExample PRIVATE shapelib::shp)
