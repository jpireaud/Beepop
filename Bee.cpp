// Bee.cpp : implementation file
//

#include "Bee.h"
#include "VarroaPop.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBee

IMPLEMENT_DYNCREATE(CBee, CCmdTarget)

CBee::CBee()
{
	number = 0;
	age = 0.0;
	Alive = true;
}

CBee::~CBee()
{
}

CBee CBee::operator=(CBee& bee)
{
	CBee temp;
	temp.number = bee.number;
	temp.age = bee.age;
	temp.Alive = bee.Alive;
	return temp;
}

CBee::CBee(int Num)
{
	age = 0.0;
	number = Num;
	Alive = true;
}

CBee::CBee(CBee& bee)
{
	number = bee.number;
	age = bee.age;
	Alive = bee.Alive;
}

BEGIN_MESSAGE_MAP(CBee, CCmdTarget)
//{{AFX_MSG_MAP(CBee)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBee message handlers

void CBee::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{ // storing code
		ar << number;
		ar << age;
	}
	else
	{ // loading code
		ar >> number;
		ar >> age;
	}
}
