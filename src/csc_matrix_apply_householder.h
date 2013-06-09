// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_APPLY_HOUSEHOLDER_H_
#define _CSC_MATRIX_APPLY_HOUSEHOLDER_H_

template<class idx_type, class el_type>
void csc_matrix<idx_type, el_type>::apply_householder(idx_type column, el_type beta, std::vector<el_type>& vec) const
{
    auto temp = el_type();
    for (auto offset = m_col_idx[column]; offset != m_col_idx[column + 1]; offset ++)
    {
        temp += (vec[m_row_idx[offset]] * m_x[offset]);
    }
    
    for (auto offset = m_col_idx[column]; offset != m_col_idx[column + 1]; offset ++)
    {
        vec[m_row_idx[offset]] -= (beta * temp * m_x[offset]);
    }
}
#endif
