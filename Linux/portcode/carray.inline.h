template<class TYPE, class ARG_TYPE>
BOOL CArray<TYPE, ARG_TYPE>::IsEmpty() const
{
    return m_data.empty();
}

template<class TYPE, class ARG_TYPE>
INT_PTR CArray<TYPE, ARG_TYPE>::GetCount() const
{
    return m_data.size();
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::RemoveAll()
{
    return m_data.clear();
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::Copy(const CArray<TYPE, ARG_TYPE>& array)
{
    if (this != &array)
    {
        m_data = array.m_data;
    }
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::Add(const TYPE& element)
{
    return m_data.push_back(element);
}

template<class TYPE, class ARG_TYPE>
const TYPE& CArray<TYPE, ARG_TYPE>::operator[](INT_PTR index) const
{
    return m_data[index];
}

template<class TYPE, class ARG_TYPE>
TYPE& CArray<TYPE, ARG_TYPE>::operator[](INT_PTR index)
{
    return m_data[index];
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::RemoveAt(INT_PTR index)
{
    auto it = m_data.begin();
    std::advance(it, index);
    m_data.erase(it);
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::SetSize(INT_PTR size, INT_PTR /*growBy*/)
{
    m_data.resize(size);
}