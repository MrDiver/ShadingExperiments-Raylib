cmake_minimum_required(VERSION 3.7)
project(rlProgram)

find_package(raylib 3.7.0 REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist)
set(BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

include(CMakeOptions.txt)
#include(GNUInstallDirs)

link_libraries(raylib)
include_directories(include)

#Add projects
add_subdirectory(src/examples)

#Add Raygui

if(${USE_RAYGUI})
    add_compile_definitions(USE_RAYGUI)
    include(ExternalProject)
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/raygui")
        ExternalProject_Add(raygui
            GIT_REPOSITORY "https://github.com/raysan5/raygui"
            SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/raygui"
            SOURCE_SUBDIR "projects/CMake"
            CMAKE_ARGS
                -DBUILD_RAYGUI_EXAMPLES=OFF
                -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}
        )
    endif()
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

macro(printProjectName)
    message("Project Name:${PROJECT_NAME}")
endmacro()