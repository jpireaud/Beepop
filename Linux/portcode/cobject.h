#pragma once
#ifndef COBJECT_CUSTOM_H
#define COBJECT_CUSTOM_H

class CArchive;

class CObject
{
public:
	virtual void Serialize(CArchive& ar);
};

#endif // COBJECT_CUSTOM_H
