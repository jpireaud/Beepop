cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

message("** [DEBUG] CMAKE_HOST_SYSTEM_NAME: " ${CMAKE_HOST_SYSTEM_NAME})
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(CMAKE_GENERATOR_PLATFORM Win32)
endif()

## package manager

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.296.tar.gz"
    SHA1 "232f5022ee1d45955a7e8d3e1720f31bac1bb534"
    LOCAL
)

project(VarroaPop)

## force generator on windows to use x86 target instead of default x64 since we want to avoid char / wchar headaches 
message("** [DEBUG] MSVC: " ${MSVC})
message("** [DEBUG] MSVC_TOOLSET_VERSION: " ${MSVC_TOOLSET_VERSION})

if (${MSVC})
    message("** [DEBUG] Executing in a Visual Studio compiler")
    message("** [DEBUG] CMAKE_GENERATOR_PLATFORM " ${CMAKE_GENERATOR_PLATFORM})
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

## download dependencies

# Add PocoCPP for DateTime class
hunter_add_package(PocoCpp)

# fmt library is included from the vcpck install of it 
# follow instructions https://github.com/microsoft/vcpkg/
hunter_add_package(fmt)

# Boost framework
hunter_add_package(Boost COMPONENTS system filesystem)

# Add CXXOPTS for command line options
hunter_add_package(cxxopts)

# Compression
hunter_add_package(ZLIB)

# Include 3rd include directories
include_directories(BEFORE 3rd)

# Include 3rd gzip include directories
include_directories(BEFORE 3rd/gzip-hpp/include)

## precompiled header

set(VarroaPopPCH "${CMAKE_SOURCE_DIR}/portcode/stdafx.h")

## include directories

include_directories(BEFORE . src lib portcode datamodel)

## specific definitions

## sub directories

add_subdirectory(portcode)
add_subdirectory(datamodel)
add_subdirectory(lib)
add_subdirectory(tests)

## build application

find_package(Boost CONFIG REQUIRED system filesystem)
find_package(cxxopts CONFIG REQUIRED)
find_package(Poco REQUIRED Foundation CONFIG)
find_package(ZLIB CONFIG REQUIRED)

set (SOURCES src/main.cpp)

if (${MSVC}) 
    message("Target WIN32 on windows")
    add_executable(VarroaPop WIN32 ${SOURCES})
else ()
    message("Target OS: " ${CMAKE_SYSTEM_NAME})
    add_executable(VarroaPop ${SOURCES})
endif ()

target_link_libraries(VarroaPop PRIVATE VarroaPopCmdLib VarroaPopDataModel VarroaPopLinuxPort)
target_link_libraries(VarroaPop PRIVATE Boost::system Boost::filesystem)
target_link_libraries(VarroaPop PRIVATE cxxopts::cxxopts)
target_link_libraries(VarroaPop PRIVATE Poco::Foundation)
target_link_libraries(VarroaPop PRIVATE ZLIB::zlib)
target_precompile_headers(VarroaPop REUSE_FROM VarroaPopLinuxPort)
