#if !defined(AFX_AXISCOLLECTION_H__12DF2521_6AF6_11D4_AC53_444553546170__INCLUDED_)
#define AFX_AXISCOLLECTION_H__12DF2521_6AF6_11D4_AC53_444553546170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CAxis;

/////////////////////////////////////////////////////////////////////////////
// CAxisCollection wrapper class

class CAxisCollection : public COleDispatchDriver
{
public:
	CAxisCollection() {}		// Calls COleDispatchDriver default constructor
	CAxisCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAxisCollection(const CAxisCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetCount();
	LPDISPATCH GetParent();

// Operations
public:
	CAxis GetItem(const VARIANT& Index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AXISCOLLECTION_H__12DF2521_6AF6_11D4_AC53_444553546170__INCLUDED_)
