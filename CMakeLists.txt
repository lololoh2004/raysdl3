cmake_minimum_required(VERSION 4.1)
project(raysdl2 C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}")

set(LIB_NAME "rsdl")


# ==== SDL DLL ====
set(SDL_SHARED  ON  CACHE BOOL "Build shared SDL library" FORCE)
set(SDL_STATIC  OFF CACHE BOOL "Build static SDL library" FORCE)
set(SDL_TESTS   OFF CACHE BOOL "Disable SDL tests"        FORCE)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3" "${CMAKE_CURRENT_BINARY_DIR}/SDL3")


set(SDLSHADERCROSS_CLI      OFF CACHE BOOL "Disable shadercross CLI tool" FORCE)
set(SDLSHADERCROSS_VENDORED ON  CACHE BOOL "Use vendored dependencies"    FORCE)
set(SDLSHADERCROSS_DXC      OFF CACHE BOOL "Disable DXC support"          FORCE)
set(SDLSHADERCROSS_SHARED   ON  CACHE BOOL "Build shared shadercross"     FORCE)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3_shadercross" "${CMAKE_CURRENT_BINARY_DIR}/SDL3_shadercross")

# ==== RaylibSDL ====
set(RSDL_BASE
        # Base
        include/rsdl.h
        src/render/draw.c
        src/render/load_shader.c
        include/rsdl/window.h
        src/window/base.c
        include/rsdl_raylib_wrap.h
        include/rsdl/common/structs.h
        include/rsdl/common/enums.h
        include/rsdl/common/export_macro.h
        include/rsdl/log.h
        src/log.c
        src/window/time.c
        include/rsdl/common/default_shaders_content.h
        src/render/base.c
        src/window/events.c
        include/rsdl/cfg.h
        src/cfg.c
)

add_library(${LIB_NAME} STATIC
    ${RSDL_BASE})

target_include_directories(${LIB_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(${LIB_NAME} PUBLIC
        SDL3::SDL3-shared
        SDL3_shadercross::SDL3_shadercross
)

if (TARGET spirv-cross-c-shared)
    set_target_properties(spirv-cross-c-shared PROPERTIES
            OUTPUT_NAME "SPIRV_cross"
            DEBUG_POSTFIX ""
    )
    if(WIN32)
        set_target_properties(spirv-cross-c-shared PROPERTIES PREFIX "")
    endif()
endif()


# ==== Example ====
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(exampleBin example/src/main.cpp)
    target_link_libraries(exampleBin PRIVATE rsdl)
endif()