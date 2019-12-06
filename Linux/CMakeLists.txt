cmake_minimum_required(VERSION 3.10)

## package manager

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/Huolju/hunter/archive/v0.23.235.tar.gz"
    SHA1 "7627e6bb45424a26cb87794b8d9b4737a130089d"
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

## sub directories

add_subdirectory(portcode)
add_subdirectory(datamodel)
add_subdirectory(tests)

## build application

set (SOURCES main.cpp)

add_executable(VarroaPop ${SOURCES})
add_dependencies(VarroaPop VarroaPopDataModel VarroaPopLinuxPort)
