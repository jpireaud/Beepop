cmake_minimum_required(VERSION 3.10)

## package manager

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.235.tar.gz"
    SHA1 "d8992c8a66c1ff2f68566c658ddaa465eca844e4"
)

project(VarroaPop)

## download dependencies

# fmt library is included from the vcpck install of it 
# follow instructions https://github.com/microsoft/vcpkg/
hunter_add_package(fmt)

# unit tests framework
hunter_add_package(Catch)

# Boost framework
hunter_add_package(Boost COMPONENTS system filesystem)

## precompiled header

set(VarroaPopPCH "${CMAKE_SOURCE_DIR}/portcode/stdafx.h")

## include directories

include_directories(BEFORE . portcode datamodel)

## specific definitions

## sub directories

add_subdirectory(datamodel)
add_subdirectory(portcode)
add_subdirectory(tests)

## build application

find_package(Boost CONFIG REQUIRED system filesystem)

set (SOURCES main.cpp varroapopcmd.cpp)

add_executable(VarroaPop ${SOURCES})

target_link_libraries(VarroaPop PRIVATE VarroaPopDataModel VarroaPopLinuxPort)
target_link_libraries(VarroaPop PRIVATE Boost::system Boost::filesystem)
target_precompile_headers(VarroaPop REUSE_FROM VarroaPopDataModel)