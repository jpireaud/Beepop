#pragma once
#include "stdafx.h"

class CSnapshotInfo : public CObject
{
protected:
	COleDateTime m_date;      //!< date to generate/apply the snapshot
	CString      m_name;      //!< this name is used to save/load the snapshot to/from the snapshots directory path
	BOOL         m_scheduled; //!< when snapshot is used for a reset this will determine if it is a repetitive one

public:
	CSnapshotInfo() : m_date(), m_name(), m_scheduled(false) {}
	CSnapshotInfo(const CSnapshotInfo& other);
	virtual ~CSnapshotInfo() {}

	const COleDateTime& GetDate() const { return m_date; }
	const CString&      GetName() const { return m_name; }
	BOOL                IsScheduled() const { return m_scheduled; }

	void SetDate(const COleDateTime& date) { m_date = date; }
	void SetName(const CString& name) { m_name = name; }
	void SetScheduled(BOOL scheduled) { m_scheduled = scheduled; }
};
