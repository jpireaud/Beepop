template<class BASE_CLASS, class TYPE>
BOOL CTypedPtrList<BASE_CLASS, TYPE>::IsEmpty() const
{
    return m_data.empty();
}

template<class BASE_CLASS, class TYPE>
INT_PTR CTypedPtrList<BASE_CLASS, TYPE>::GetCount() const
{
    return m_data.size();
}

template<class BASE_CLASS, class TYPE>
TYPE CTypedPtrList<BASE_CLASS, TYPE>::GetAt(POSITION position) const
{
    auto it = reinterpret_cast<CPtrListNs::InnerPosition<TYPE>*>(position);
    return *it->m_it;
}

template<class BASE_CLASS, class TYPE>
POSITION CTypedPtrList<BASE_CLASS, TYPE>::AddTail(TYPE object)
{
    m_data.push_back(object);
    return GetTailPosition();
}

template<class BASE_CLASS, class TYPE>
void CTypedPtrList<BASE_CLASS, TYPE>::RemoveAt(POSITION position)
{
    auto it = reinterpret_cast<CPtrListNs::InnerPosition<TYPE>*>(position);
    m_data.erase(it->m_it);
}

template<class BASE_CLASS, class TYPE>
POSITION CTypedPtrList<BASE_CLASS, TYPE>::GetHeadPosition() const
{
    POSITION position = nullptr;
    if (GetCount() > 0)
    {
        m_iterator->m_it = m_data.begin();
        position = reinterpret_cast<POSITION>(m_iterator.get());
    }
    return position;
}

template<class BASE_CLASS, class TYPE>
POSITION CTypedPtrList<BASE_CLASS, TYPE>::GetTailPosition() const
{
    POSITION position = nullptr;
    if (GetCount() > 0)
    {
        m_iterator->m_it = m_data.end()--;
        position = reinterpret_cast<POSITION>(m_iterator.get());
    }
    return position;
}

template<class BASE_CLASS, class TYPE>
TYPE CTypedPtrList<BASE_CLASS, TYPE>::GetHead() const
{
    return m_data.front();
}

template<class BASE_CLASS, class TYPE>
TYPE CTypedPtrList<BASE_CLASS, TYPE>::GetTail() const
{
    return m_data.back();
}

template<class BASE_CLASS, class TYPE>
TYPE CTypedPtrList<BASE_CLASS, TYPE>::GetNext(POSITION position) const
{
    auto it = reinterpret_cast<CPtrListNs::InnerPosition<TYPE>*>(position);
    TYPE next = *it->m_it;
    it->m_it++;
    if (it->m_it == m_data.end())
    {
        position = nullptr;
    }
    return next;
}

template<class BASE_CLASS, class TYPE>
TYPE CTypedPtrList<BASE_CLASS, TYPE>::RemoveHead() 
{
    TYPE head = GetHead();
    m_data.pop_front();
}

template<class BASE_CLASS, class TYPE>
void CTypedPtrList<BASE_CLASS, TYPE>::RemoveAll() 
{
    m_data.clear();
}
