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

if(WIN32)
    add_library(SDL3_IMPORTED SHARED IMPORTED)
    set_target_properties(SDL3_IMPORTED PROPERTIES
            IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/SDL3.dll"
            IMPORTED_IMPLIB   "${CMAKE_CURRENT_SOURCE_DIR}/libSDL3.dll.a"
            INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3/include"
    )

    add_library(Shadercross_IMPORTED SHARED IMPORTED)
    set_target_properties(Shadercross_IMPORTED PROPERTIES
            IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/SDL3_shadercross.dll"
            IMPORTED_IMPLIB   "${CMAKE_CURRENT_SOURCE_DIR}/libSDL3_shadercross.dll.a"
            INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3_shadercross/include"
    )
else()
    add_library(SDL3_IMPORTED SHARED IMPORTED)
    set_target_properties(SDL3_IMPORTED PROPERTIES
            IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libSDL3.so"
    )
    add_library(Shadercross_IMPORTED SHARED IMPORTED)
    set_target_properties(Shadercross_IMPORTED PROPERTIES
            IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libSDL3_shadercross.so"
    )
endif()

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

add_library(${LIB_NAME} STATIC ${RSDL_BASE})

target_include_directories(${LIB_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(${LIB_NAME} PUBLIC
        SDL3_IMPORTED
        Shadercross_IMPORTED
)


# ==== Example ====
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(exampleBin example/src/main.cpp)
    target_link_libraries(exampleBin PRIVATE rsdl)
endif()