#find_package(Raylib 3.7.0 REQUIRED)

set(SOURCE_FILES
    raylib_imgui.cpp
)

set(HEADER_FILES
    raylib_imgui.h
)

add_library(RaylibImGui ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(RaylibImGui PRIVATE "${PROJECT_SOURCE_DIR}/include/imgui")
target_include_directories(RaylibImGui PUBLIC "${PROJECT_SOURCE_DIR}/")

#if(NOT EXISTS raylib)
    #find_package(raylib 3.7.0 REQUIRED)
#endif()
target_link_libraries(RaylibImGui PRIVATE raylib ${CMAKE_DL_LIBS})


set(CMAKE_C_STANDARD 99)
set_target_properties(RaylibImGui PROPERTIES LINKER_LANGUAGE C)
