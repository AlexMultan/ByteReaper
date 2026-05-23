cmake_minimum_required(VERSION 3.20)
project(engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(OUTPUT_DIR "${CMAKE_BUILD_TYPE}-x64")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")

if(MSVC)
    add_compile_options(/utf-8)
    add_compile_definitions(BYTEREAPER_PLATFORM_WIN64)
endif()

add_compile_definitions(
        $<$<CONFIG:Debug>:ENGINE_DEBUG>
        $<$<CONFIG:Release>:ENGINE_RELEASE>
        $<$<CONFIG:Shipping>:ENGINE_SHIPPING>
)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
add_subdirectory(engine/vendor/SDL)
add_subdirectory(engine/vendor/imgui)
add_subdirectory(engine/vendor/spdlog)
set(JSON_BuildTests OFF CACHE BOOL "" FORCE)
add_subdirectory(engine/vendor/json)

add_subdirectory(engine/vendor/mio)

add_subdirectory(engine/vendor/RapidFuzz)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE engine/vendor/stb)

set(IMGUI_INCLUDE  "engine/vendor/ImGui")
set(SPDLOG_INCLUDE "engine/vendor/spdlog/include")
set(SDL_INCLUDE    "engine/vendor/SDL/include")

file(GLOB_RECURSE ENGINE_SOURCES
        "engine/src/**.h"
        "engine/src/**.cpp"
)

if(CMAKE_BUILD_TYPE STREQUAL "Shipping")
    add_library(EngineLib STATIC ${ENGINE_SOURCES})
    target_compile_definitions(EngineLib PUBLIC ENGINE_STATIC)
else()
    add_library(EngineLib SHARED ${ENGINE_SOURCES})
    target_compile_definitions(EngineLib PUBLIC ENGINE_BUILD_DLL)
endif()

set_target_properties(EngineLib PROPERTIES
        OUTPUT_NAME "Engine"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}/engine"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}/engine"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}/engine"
)

find_package(OpenGL REQUIRED)

target_include_directories(EngineLib PUBLIC
        ${SDL_INCLUDE}
        ${IMGUI_INCLUDE}
        ${SPDLOG_INCLUDE}
        "engine"
)

target_link_libraries(EngineLib PUBLIC
        SDL3::SDL3-static
        OpenGL::GL
        imgui
        spdlog::spdlog
        nlohmann_json::nlohmann_json
        mio::mio
        rapidfuzz::rapidfuzz
        stb
)

if(MSVC)
    target_link_libraries(EngineLib PUBLIC imm32)
    target_compile_options(EngineLib PRIVATE
            $<$<CONFIG:Debug>:/MDd>
            $<$<CONFIG:Release>:/MD>
            $<$<CONFIG:Shipping>:/MD>
    )
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL "Shipping")
    add_custom_command(TARGET EngineLib POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}/editor"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:EngineLib>
            "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}/editor"
    )
endif()

file(GLOB_RECURSE EDITOR_SOURCES
        "editor/src/**.h"
        "editor/src/**.cpp"
)

add_executable(editor ${EDITOR_SOURCES})

set_target_properties(editor PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}/editor"
)

target_include_directories(editor PRIVATE
        ${SDL_INCLUDE}
        ${IMGUI_INCLUDE}
        ${SPDLOG_INCLUDE}
        "engine/src"
        "editor/src"
)

target_link_libraries(editor PRIVATE
        EngineLib
        SDL3::SDL3-static
        OpenGL::GL
        imgui
        spdlog::spdlog
        nlohmann_json::nlohmann_json
        mio::mio
        rapidfuzz::rapidfuzz
        stb
)

if(MSVC)
    target_link_libraries(editor PRIVATE imm32)
    target_compile_options(editor PRIVATE
            $<$<CONFIG:Debug>:/MDd>
            $<$<CONFIG:Release>:/MD>
            $<$<CONFIG:Shipping>:/MD>
    )
endif()