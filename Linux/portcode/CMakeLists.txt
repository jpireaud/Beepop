cmake_minimum_required(VERSION 3.10)

find_package(fmt CONFIG REQUIRED)
# find_package(Boost CONFIG REQUIRED)

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
            cstdiofile.cpp
            cstring.cpp
            cstringarray.cpp
            ctime.cpp
            cuintarray.cpp )

add_library(VarroaPopLinuxPort ${SOURCES})
target_link_libraries(VarroaPopLinuxPort fmt::fmt)
