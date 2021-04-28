#include "SnapshotInfo.h"

CSnapshotInfo::CSnapshotInfo(const CSnapshotInfo& other)
    : m_date(
          other.m_date.GetYear(), other.m_date.GetMonth(), other.m_date.GetDay(), other.m_date.GetHour(),
          other.m_date.GetMinute(), 0),
      m_name(other.m_name), m_scheduled(other.m_scheduled)
{
}
