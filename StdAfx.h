// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
//
#if !defined(AFX_STDAFX_H__8C6C4189_7899_11D2_8D9A_0020AF233A70__INCLUDED_)
#define AFX_STDAFX_H__8C6C4189_7899_11D2_8D9A_0020AF233A70__INCLUDED_


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afx.h>
#include <afxdlgs.h>

extern bool gl_RunGUI;

#include <iostream>

#define NOT_IMPLEMENTED()                                                                                              \
	std::cerr << __FUNCTION__ << ": NOT IMPLEMENTED in " << __FILE__ << "(" << __LINE__ << ")" << std::endl;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8C6C4189_7899_11D2_8D9A_0020AF233A70__INCLUDED_)
