// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CVcAxisScale wrapper class

class CVcAxisScale : public COleDispatchDriver
{
public:
	CVcAxisScale() {}		// Calls COleDispatchDriver default constructor
	CVcAxisScale(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcAxisScale(const CVcAxisScale& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetHide();
	void SetHide(BOOL bNewValue);
	long GetType();
	void SetType(long nNewValue);
	short GetLogBase();
	void SetLogBase(short nNewValue);
	long GetPercentBasis();
	void SetPercentBasis(long nNewValue);
};
