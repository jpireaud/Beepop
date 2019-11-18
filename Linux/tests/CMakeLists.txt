cmake_minimum_required(VERSION 3.10)

# find_package(Catch2 CONFIG REQUIRED)

set(SOURCES main.cpp
            test_cstring.cpp )

add_executable(VarroaPopTests ${SOURCES})
target_link_libraries(VarroaPopTests PRIVATE VarroaPopDataModel VarroaPopLinuxPort)
# target_link_libraries(VarroaPopTests PRIVATE Catch2::Catch2)
