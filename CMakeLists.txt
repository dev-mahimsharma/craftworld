cmake_minimum_required(VERSION 3.20)

project(craftworld LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put the executable directly in build/ for the run script.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hh"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hxx"
)

foreach(path IN LISTS PROJECT_SOURCES PROJECT_HEADERS)
    if(path MATCHES "[/\\\\]build[/\\\\]" OR path MATCHES "[/\\\\]CMakeFiles[/\\\\]")
        list(REMOVE_ITEM PROJECT_SOURCES "${path}")
        list(REMOVE_ITEM PROJECT_HEADERS "${path}")
    endif()
endforeach()

if(NOT PROJECT_SOURCES)
    message(FATAL_ERROR "No C/C++ source files found. Add at least one .c, .cc, .cpp, or .cxx file, then run build_and_run.bat again.")
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

set(header_dirs "")
foreach(header IN LISTS PROJECT_HEADERS)
    get_filename_component(header_dir "${header}" DIRECTORY)
    list(APPEND header_dirs "${header_dir}")
endforeach()

if(header_dirs)
    list(REMOVE_DUPLICATES header_dirs)
    target_include_directories(${PROJECT_NAME} PRIVATE ${header_dirs})
endif()
