cmake_minimum_required(VERSION 3.10)

## package manager

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.232.tar.gz"
    SHA1 "413fcd1a89b7b484e89e9ab6bf7996550335a7e8"
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
