cmake_minimum_required(VERSION 3.10)

find_package(Catch2 CONFIG REQUIRED)

set(SOURCES main.cpp
            test_carray.cpp
            test_cmapstringtoob.cpp
            test_coblist.cpp
            test_cptrlist.cpp
            test_cstring.cpp )

add_executable(VarroaPopTests ${SOURCES})
target_link_libraries(VarroaPopTests PRIVATE VarroaPopDataModel VarroaPopLinuxPort)
target_link_libraries(VarroaPopTests PRIVATE Catch2::Catch2)
target_precompile_headers(VarroaPopTests REUSE_FROM VarroaPopDataModel)
