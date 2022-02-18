cmake_minimum_required(VERSION 3.10)

find_package(fmt CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED system filesystem)
find_package(Poco REQUIRED Foundation CONFIG)

set(SOURCES carchive.cpp
            carray.cpp
            ccmdtarget.cpp
            cdialog.cpp
            cfile.cpp
            cmapstringtoob.cpp
            cobject.cpp
            coblist.cpp
            coledatetime.cpp
            cptrlist.cpp
            cstring.cpp
            cstringarray.cpp
            ctime.cpp
            cuintarray.cpp
            position.cpp
            stdafx.cpp
            varroapop.cpp )

set(INCLUDES    carchive.h
                carray.h
                ccmdtarget.h
                cdialog.h
                cfile.h
                cmapstringtoob.h
                cobject.h
                coblist.h
                coledatetime.h
                cptrlist.h
                cstring.h
                cstringarray.h
                ctime.h
                cuintarray.h
                position.h
                stdafx.h
                varroapop.h )

add_library(VarroaPopLinuxPort ${SOURCES} ${INCLUDES})
target_link_libraries(VarroaPopLinuxPort PRIVATE fmt::fmt)
target_link_libraries(VarroaPopLinuxPort PRIVATE Boost::system Boost::filesystem)
target_link_libraries(VarroaPopLinuxPort PRIVATE Poco::Foundation)
target_precompile_headers(VarroaPopLinuxPort PRIVATE "${VarroaPopPCH}")
