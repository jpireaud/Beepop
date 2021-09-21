cmake_minimum_required(VERSION 3.10)

find_package(fmt CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED system filesystem)
find_package(Poco REQUIRED Foundation CONFIG)

set(SOURCES agestructureoutputformatter.cpp
            colonysizeoutputformatter.cpp
            csv.cpp
            customoutputformatter.cpp
            debugoutputformatter.cpp
            mapdataoutputformatter.cpp
            varroapopcmdbridge.cpp )

set(INCLUDES    agestructureoutputformatter.h
                colonysizeoutputformatter.h
                csv.h
                customoutputformatter.h
                debugoutputformatter.h
                mapdataoutputformatter.h
                varroapopcmdbridge.h )

add_library(VarroaPopCmdLib ${SOURCES} ${INCLUDES})
target_link_libraries(VarroaPopCmdLib PRIVATE fmt::fmt)
target_link_libraries(VarroaPopCmdLib PRIVATE Boost::system Boost::filesystem)
target_link_libraries(VarroaPopCmdLib PRIVATE Poco::Foundation)
target_precompile_headers(VarroaPopCmdLib REUSE_FROM VarroaPopLinuxPort)
