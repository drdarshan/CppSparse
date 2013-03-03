// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_SPARSE_LOWER_SOLVE_H_
#define _CSC_MATRIX_SPARSE_LOWER_SOLVE_H_

template<class idx_type, class el_type> 
csc_matrix<idx_type, el_type> 
csc_matrix<idx_type, el_type>::sparse_lower_solve(const typename csc_matrix<idx_type, el_type>::idx_vector_type& parent,
                                                  const csc_matrix<idx_type, el_type>& rhs) const
{
    // Mark = True <=> Xi != 0
    std::vector<bool> mark(m_n_rows, false);
    idx_type nonzeros = 0;

    // Symbolic computation step, find the number of nonzeros of X and the
    // non-zero pattern using the array Mark
    for (auto offset = rhs.m_col_idx[0]; offset != rhs.m_col_idx[1]; offset ++)
    {
        auto col = rhs.m_row_idx[offset];

        for (auto offset2 = m_col_idx[col]; offset2 != m_col_idx[col + 1]; offset2 ++)
        {
            auto row = m_row_idx[offset2];

            while(row != npos || !mark[row])
            {
                mark[row] = true;
                nonzeros ++;
                row = parent[row];
            }
        }
    }
    
    // Scatter RHS into temporary result
    std::vector<el_type> tresult(m_n_rows);
    for (auto offset = 0; offset < rhs.m_col_idx[1]; offset ++)
    {
        tresult[rhs.m_row_idx[offset]] = rhs.m_x[offset];
    }
    

    // Compute the final result
    // Symbolic computation step, find the number of nonzeros of X and the
    // non-zero pattern using the array Mark
    for (auto offset = 0; offset != rhs.m_col_idx[1]; offset ++)
    {
        auto col = rhs.m_row_idx[offset];
        
        auto offset2 = m_col_idx[col];

        // X[i] /= L[i,i];
        tresult[col] /= m_x[offset2];
        offset2 ++;

        auto xi = tresult[col];
        // X[j] -= L[j,i] X[i];
        for (; offset2 != m_col_idx[col + 1]; offset2 ++)
        {
            auto row = m_row_idx[offset2];
            tresult[row] -= m_x[offset2] * xi;
        }
    }
           
    // Now gather the indices and values of tresult into result
    csc_matrix<idx_type, el_type> result(m_n_rows, 1, nonzeros);
    result.m_col_idx[0] = 0; result.m_col_idx[1] = nonzeros;
    result.m_row_idx.resize(nonzeros);
    result.m_x.resize(nonzeros);

    idx_type nonzeroindex = 0;
    for (auto elem = 0; elem < m_n_rows; elem ++)
    {
        if (mark[elem])
        {
            result.m_row_idx[nonzeroindex] = elem;
            result.m_x[nonzeroindex] = tresult[elem];
            nonzeroindex ++;
        }
    }
    
    return result;
}
#endif

