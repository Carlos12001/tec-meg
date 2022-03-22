cmake_minimum_required(VERSION 3.21)
project(tec-meg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++20")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/")

#Add Qt config to file
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Tell cmake to find the modules Qt5Widgets
find_package(Qt5Widgets REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.h")
add_executable("${CMAKE_PROJECT_NAME}" "${SOURCE_FILES}")

# Link the library to the executable
target_link_libraries("${CMAKE_PROJECT_NAME}" Qt5::Widgets)