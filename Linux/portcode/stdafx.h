#pragma once
#ifndef STDAFX_CUSTOM_H
#define STDAFX_CUSTOM_H

#define DECLARE_DYNCREATE(Class) public:
#define IMPLEMENT_DYNCREATE(Class, BaseClass) // void

#define DECLARE_SERIAL(Class) // void
#define IMPLEMENT_SERIAL(Class, BaseClass, Offset) // void

#define DECLARE_MESSAGE_MAP() // void
#define BEGIN_MESSAGE_MAP(Class, BaseClass) // void
#define END_MESSAGE_MAP() // void

#define DDX_Text(_1, _2, _3) // void
#define DDV_MinMaxInt(_1, _2, _3, _4) // void
#define DDX_Radio(_1, _2, _3) // void

#define afx_msg 

#define XSTR(x) STR(x)
#define STR(x) #x

#include <cassert>
#define ASSERT assert

#include <memory>
#define DEBUG_NEW new

#include "fmt/printf.h"
#define TRACE(...) fmt::printf(__VA_ARGS__)

#ifndef WINDOWS
#if _WIN32 || _WIN64
#define WINDOWS
#endif
#endif

#include <cstdint>
typedef int32_t BOOL;
typedef unsigned char BYTE;
typedef BYTE BOOLEAN;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef uint32_t UINT;
typedef char* LPTSTR;
typedef const char* LPCTSTR;
typedef char TCHAR;
typedef intptr_t INT_PTR;
typedef long LONG;
typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;

#ifndef WINDOWS
#ifndef _SYSTEMTIME_
#define _SYSTEMTIME_
typedef struct _SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME;
typedef struct _SYSTEMTIME *PSYSTEMTIME;
typedef struct _SYSTEMTIME *LPSYSTEMTIME;
typedef struct {
    SYSTEMTIME st;
    WORD  wDayOfYear;
} UDATE;
#endif
#else
#define NOMINMAX
#include <windows.h>
#endif

#define TRUE true
#define FALSE false

// Abstract iteration position check if we can change to a size_t
struct __POSITION {};
typedef __POSITION* POSITION;

#include "carchive.h"
#include "carray.h"
#include "cobject.h"
#include "cdialog.h"
#include "ccmdtarget.h"
#include "cfile.h"
#include "cmapstringtoob.h"
#include "coblist.h"
#include "coledatetime.h"
#include "cptrlist.h"
#include "cstring.h"
#include "cstringarray.h"
#include "ctime.h"
#include "cuintarray.h"

#include "fmt/format.h"
template<>
struct fmt::formatter<CString>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx);

    template<typename FormatContext>
    auto format(CString const& number, FormatContext& ctx);
};
#include "fmt/ostream.h"
std::ostream &operator<<(std::ostream &stream, const CString& string);

#include "cstring.format.h"

#if !defined(_WIN32) && !defined(_WIN64) && !defined(__STDC_LIB_EXT1__)
#define strcpy_s strcpy
#define strtok_s(_In, _Delim, _SafeToken) strtok(_In, _Delim)
#endif

#define NOT_IMPLEMENTED() assert("Not implemented!")

#endif // STDAFX_CUSTOM_H

