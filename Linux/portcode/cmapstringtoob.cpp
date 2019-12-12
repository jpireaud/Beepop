#include "cmapstringtoob.h"

bool CMapStringToOb::IsEmpty() const
{
    return m_map.empty();
}

POSITION CMapStringToOb::GetStartPosition() const
{
    // initialize iterator 
    m_iterator.reset(new CMapStringToObNs::InnerPosition);
    m_iterator->m_it = m_map.begin();

    auto position = reinterpret_cast<POSITION>(m_iterator.get());
    return position;
}

void CMapStringToOb::SetAt(CString& string, CObject* value)
{
    m_map[string] = value;
}

void CMapStringToOb::GetNextAssoc(POSITION& position, CString& string, CObject*& value) const
{
    auto iterator = reinterpret_cast<CMapStringToObNs::InnerPosition*>(position);
    string = iterator->m_it->first;
    value = iterator->m_it->second;
    iterator->m_it++;
}

bool CMapStringToOb::Lookup(CString& string, CObject*& value) const
{
    auto it = m_map.find(string);
    return it!=m_map.end() && it->second == value;
}

void CMapStringToOb::RemoveKey(CString& string)
{
    // here for now I don't update the current InnerPosition since
    // we should have incremented the iterator before erasing the key
    // hence the iterator on next will still be valid
    m_map.erase(string);
}
