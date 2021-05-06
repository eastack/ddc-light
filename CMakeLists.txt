cmake_minimum_required(VERSION 3.19)
project(ddc-light C)

find_package(GTK REQUIRED)
find_package (PkgConfig REQUIRED)
pkg_check_modules(DDCUTIL REQUIRED)

include_directories(${GTK3_INCLUDE_DIRS} ${LIBDDCUTIL_INCLUDE_DIRS})
link_libraries(${GTK3_LIBRARIES} ${LIBDDCUTIL_LIBRARY})

set(CMAKE_C_STANDARD 99)
add_executable(${PROJECT_NAME} main.c)
