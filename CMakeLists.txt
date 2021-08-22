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

link_libraries(raylib ${CMAKE_DL_LIBS})

#Add Raygui

include(ExternalProject)
if(${USE_RAYGUI})
    add_compile_definitions(USE_RAYGUI)
    if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/raygui OR ${FORCE_UPDATE})
        ExternalProject_Add(raygui
            GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
            SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/raygui"
            SOURCE_SUBDIR "projects/CMake"
            CMAKE_ARGS
                -DBUILD_RAYGUI_EXAMPLES=OFF
                -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/include/raygui
        )
    endif()

    include_directories(${PROJECT_SOURCE_DIR}/include/raygui/include)
endif()

#Add ImGui
if(${USE_IMGUI})
    #Check Version
    add_custom_target(DearImGui ALL
        ${PROJECT_SOURCE_DIR}/imgui_version.sh > ${PROJECT_SOURCE_DIR}/external/imgui.version
        BYPRODUCTS ${PROJECT_SOURCE_DIR}/external/imgui.version
                   ${PROJECT_SOURCE_DIR}/external/imgui-${IMGUI_TAG}.zip
                   ${PROJECT_SOURCE_DIR}/external/imgui-${IMGUI_TAG}
    )
    file(READ ${PROJECT_SOURCE_DIR}/external/imgui.version TMP1)
    string(STRIP ${TMP1} TMP2)
    string(COMPARE EQUAL "v${IMGUI_TAG}" "${TMP2}" isTrue)
    if(${isTrue} EQUAL 1)
        message("Your Version of Dear ImGUI is up to date VERSION ${TMP2}")
    endif()
    if(${isTrue} EQUAL 0)
        message(WARNING "Your Version of Dear ImGUI out of date NEWVERSION ${TMP2} please consider changing the tag in CMakeOptions.txt")
    endif()

    # Configure
    add_compile_definitions(USE_IMGUI)
    if(${FORCE_UPDATE} OR (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/imgui-${IMGUI_TAG}.zip"))
        message("Downloading Dear ImGui")
        file(DOWNLOAD "https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_TAG}.zip" "${PROJECT_SOURCE_DIR}/external/imgui-${IMGUI_TAG}.zip" SHOW_PROCRESS)
    endif()

    if(${FORCE_UPDATE} OR (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/imgui-${IMGUI_TAG}" AND EXISTS "${PROJECT_SOURCE_DIR}/external/imgui-${IMGUI_TAG}.zip"))
        file(ARCHIVE_EXTRACT INPUT "${PROJECT_SOURCE_DIR}/external/imgui-${IMGUI_TAG}.zip"
            DESTINATION "${PROJECT_SOURCE_DIR}/external"
            PATTERNS "*glfw.*" "imgui-${IMGUI_TAG}/imconfig.h" "imgui-${IMGUI_TAG}/imgui*.cpp" "imgui-${IMGUI_TAG}/imgui*.h" "imgui-${IMGUI_TAG}/imstb*.h" "*opengl3.cpp" "*opengl3.h" "*opengl3_loader.h"
        )
    endif()

    if(${FORCE_UPDATE} OR (NOT EXISTS "${PROJECT_SOURCE_DIR}/include/imgui" OR ${FORCE_UPDATE}))
        file(COPY "${PROJECT_SOURCE_DIR}/external/imgui-${IMGUI_TAG}/" DESTINATION "${PROJECT_SOURCE_DIR}/include/imgui")
    endif()

    include_directories(${PROJECT_SOURCE_DIR}/include/imgui)
endif()


#Add projects
add_subdirectory(src/examples)


# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
