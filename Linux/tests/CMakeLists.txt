cmake_minimum_required(VERSION 3.10)

find_package(Boost CONFIG REQUIRED system filesystem)
find_package(Poco REQUIRED Foundation CONFIG)

# source_group(tests REGULAR_EXPRESSION test_*)
# source_group(helpers REGULAR_EXPRESSION helpers/*)

set(SOURCES main.cpp
            helpers/common.cpp
            helpers/myobject.cpp
            helpers/testoutputformatter.cpp
            test_aging.cpp
            test_carchive.cpp
            test_carray.cpp
            test_cfile.cpp
            test_cmapstringtoob.cpp
            test_coblist.cpp
            test_coledatetime.cpp
            test_cptrlist.cpp
            test_cstring.cpp
            test_cstringarray.cpp
            test_cstringlist.cpp
            test_ctime.cpp
            test_cuintarray.cpp
            test_globaloptions.cpp
            test_temperaturedata.cpp
            test_validatealgorithms.cpp
            test_varroapop.cpp )

set(INCLUDES    helpers/common.h
                helpers/myobject.h
                helpers/testoutputformatter.h )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX src FILES ${SOURCES} ${INCLUDES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX data FILES *)

add_executable(VarroaPopTests ${SOURCES} ${INCLUDES})
target_link_libraries(VarroaPopTests PRIVATE VarroaPopCmdLib VarroaPopDataModel VarroaPopLinuxPort)
target_link_libraries(VarroaPopTests PRIVATE Boost::system Boost::filesystem)
target_link_libraries(VarroaPopTests PRIVATE Poco::Foundation)
target_precompile_headers(VarroaPopTests REUSE_FROM VarroaPopLinuxPort)
