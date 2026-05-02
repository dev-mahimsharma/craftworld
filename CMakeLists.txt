# ==============================================================================
# File: CMakeLists.txt
# Brief: Main CMake build configuration for Craftworld.
#
# Details:
#   CMake is the tool that generates the actual build files used by Ninja. This
#   file tells CMake which programming languages the project uses, which source
#   files belong to the executable, how raylib should be found or downloaded,
#   and which libraries must be linked.
#
#   For a beginner: this file is the build recipe. It does not run the game by
#   itself; it explains how the game should be compiled into craftworld.exe.
#
# Copyright 2026 Craftworld contributors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0
# ==============================================================================

cmake_minimum_required(VERSION 3.20)

project(craftworld LANGUAGES C CXX)

# Use modern C/C++ language modes while keeping compiler-specific extensions
# disabled. This makes the project easier to move between compilers later.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json. Editors and language servers read this file
# to understand the real compiler flags and include paths used by the project.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ninja is a single-configuration generator, so it needs a default build type.
# Visual Studio and other multi-configuration generators choose Debug/Release
# during the build command, so they are intentionally left alone here.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Put craftworld.exe directly in build/ so build_and_run.bat can launch it from
# one predictable path.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Collect all C/C++ source files under src/. CONFIGURE_DEPENDS asks CMake to
# rescan these globs when files are added or removed.
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

# Header files are listed in the target so IDEs show the complete project tree.
# CMake does not compile headers directly, but including them improves editor
# navigation and keeps source/header ownership visible.
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx"
)

if(NOT PROJECT_SOURCES)
    message(FATAL_ERROR "No C/C++ source files found. Add at least one .c, .cc, .cpp, or .cxx file, then run build_and_run.bat again.")
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Every directory that contains a project header becomes an include directory.
# This keeps includes simple while the project is still small.
set(header_dirs "")
foreach(header IN LISTS PROJECT_HEADERS)
    get_filename_component(header_dir "${header}" DIRECTORY)
    list(APPEND header_dirs "${header_dir}")
endforeach()

if(header_dirs)
    list(REMOVE_DUPLICATES header_dirs)
    target_include_directories(${PROJECT_NAME} PRIVATE ${header_dirs})
endif()

# Prefer an installed raylib package when one exists. If raylib is not installed,
# the FetchContent block below downloads the pinned release automatically.
find_package(raylib CONFIG QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)

    # Disable raylib extras so the build only produces the library needed by
    # Craftworld, not raylib examples or tests.
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# raylib on Windows/MinGW needs these platform libraries for audio, graphics,
# windowing, and timing support.
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32 opengl32)
endif()
