#if !defined(AFX_FILLSTYLE_H__12DF2556_6AF6_11D4_AC53_444553546170__INCLUDED_)
#define AFX_FILLSTYLE_H__12DF2556_6AF6_11D4_AC53_444553546170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CInterior;

/////////////////////////////////////////////////////////////////////////////
// CFillStyle wrapper class

class CFillStyle : public COleDispatchDriver
{
public:
	CFillStyle() {}		// Calls COleDispatchDriver default constructor
	CFillStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFillStyle(const CFillStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetPattern();
	void SetPattern(long);
	LPDISPATCH GetParent();
	CInterior GetInterior();
	BOOL GetIsDefault();
	void SetIsDefault(BOOL);

// Operations
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILLSTYLE_H__12DF2556_6AF6_11D4_AC53_444553546170__INCLUDED_)
