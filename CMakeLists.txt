cmake_minimum_required(VERSION 3.19)
project(ddc-light C)
set(CMAKE_C_STANDARD 99)

find_package(GTK REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(DDCUTIL REQUIRED ddcutil)

include_directories(${GTK_INCLUDE_DIRS} ${DDCUTIL_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.c ddc.h ddc.c)

target_link_libraries(ddc-light PRIVATE ${GTK_LIBRARIES} ${DDCUTIL_LIBRARIES})
