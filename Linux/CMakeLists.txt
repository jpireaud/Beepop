cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

## package manager

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.296.tar.gz"
    SHA1 "232f5022ee1d45955a7e8d3e1720f31bac1bb534"
)

project(VarroaPop)

## download dependencies

# Add PocoCPP for DateTime class
hunter_add_package(PocoCpp)

# fmt library is included from the vcpck install of it 
# follow instructions https://github.com/microsoft/vcpkg/
hunter_add_package(fmt)

# unit tests framework
hunter_add_package(Catch)

# Boost framework
hunter_add_package(Boost COMPONENTS system filesystem)

# Add CXXOPTS for command line options
hunter_add_package(cxxopts)

# Compression
hunter_add_package(ZLIB)

# Include 3rd include directories
include_directories(BEFORE 3rd/gzip-hpp/include)

## precompiled header

set(VarroaPopPCH "${CMAKE_SOURCE_DIR}/portcode/stdafx.h")

## include directories

include_directories(BEFORE . src portcode datamodel)

## specific definitions

## sub directories

add_subdirectory(portcode)
add_subdirectory(datamodel)
add_subdirectory(tests)

## build application

find_package(Boost CONFIG REQUIRED system filesystem)
find_package(cxxopts CONFIG REQUIRED)
find_package(Poco REQUIRED Foundation CONFIG)
find_package(ZLIB CONFIG REQUIRED)

set (SOURCES src/main.cpp src/csv.cpp src/varroapopcmdbridge.cpp src/customoutputformatter.cpp src/colonysizeoutputformatter.cpp)

# add_executable(VarroaPop WIN32 ${SOURCES})
add_executable(VarroaPop ${SOURCES})

target_link_libraries(VarroaPop PRIVATE VarroaPopDataModel VarroaPopLinuxPort)
target_link_libraries(VarroaPop PRIVATE Boost::system Boost::filesystem)
target_link_libraries(VarroaPop PRIVATE cxxopts::cxxopts)
target_link_libraries(VarroaPop PRIVATE Poco::Foundation)
target_link_libraries(VarroaPop PRIVATE ZLIB::zlib)
target_precompile_headers(VarroaPop REUSE_FROM VarroaPopLinuxPort)