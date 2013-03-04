// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_SPARSE_UPPER_SOLVE_H_
#define _CSC_MATRIX_SPARSE_UPPER_SOLVE_H_

template<class idx_type, class el_type> 
csc_matrix<idx_type, el_type> 
csc_matrix<idx_type, el_type>::sparse_upper_solve(const typename csc_matrix<idx_type, el_type>::idx_vector_type& parent,
                                                  const csc_matrix<idx_type, el_type>& rhs) const
{
    // Mark = True <=> Xi != 0
    std::vector<bool> mark(m_n_rows);
    idx_type nonzeros = 0;

    // Symbolic computation step, find the number of nonzeros of X and the
    // non-zero pattern using the array Mark
    

    // Start at column N-1 and go on to column 0
    // For each diagonal entry, i, check if B[i] != 0.
    // if B[i] != 0 => X[i] != 0
    // else, walk up the elimination tree at i
    // see if you hit a marked node.
    // If you hit a marked node them X[i] != 0.
    // Otherwise X[i] = 0 and you can skip i during numerical factorization.

    idx_type col = 0, j = m_n_cols - 1, offsetrhs = rhs.m_col_idx[1] - 1 ;
    for (; col < m_n_cols; col ++, j --)
    {
        // If B[j] != 0, then X[j] != 0
        if (j == rhs.m_row_idx[offsetrhs])
        {
            mark[j] = true;
            offsetrhs --;
            continue;
        }
        
        // Walk up the elimination tree, see if there exists i in ancestor[j]
        // such that X[i] != 0. If so, X[j] != 0 too.
        for (auto offset = m_col_idx[j] + 1; offset != m_col_idx[j+1]; offset ++)
        {
            auto row = m_row_idx[offset];
            while (row != npos || !mark[row])
            {
                row = parent[row];
            }
            if (row != npos)
            {
                mark[j] = true;
                break;
            }
        }
    }
    
    // Scatter RHS into temporary result
    std::vector<el_type> tresult(m_n_rows);
    idx_type numnonzeros = 0;

    for (auto offset = 0; offset < rhs.m_col_idx[1]; offset ++)
    {
        tresult[rhs.m_row_idx[offset]] = rhs.m_x[offset];
        numnonzeros ++;
    }

    for (col = 0, j = m_n_cols - 1; col < m_n_cols; col ++, j --)
    {
        // if j is not marked, skip it
        if (!mark[j])
        {
            continue;
        }

        auto lii = m_x[m_col_idx[j]];

        for (auto offset = m_col_idx[j] + 1; offset != m_col_idx[j+1]; offset ++)
        {
            auto row = m_row_idx[offset];
            if (mark[row])
            {
                tresult[j] -= m_x[offset] * tresult[row];
            }
        }

        tresult[j] /= lii;
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

