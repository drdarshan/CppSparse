//-*-mode: c++-*-
#ifndef _CSC_MATRIX_ETREE_LIU_H_
#define _CSC_MATRIX_ETREE_LIU_H_

template<class idx_type, class el_type>
typename csc_matrix<idx_type, el_type>::idx_vector_type csc_matrix<idx_type, el_type>::etree_liu() const
{
    if (n_rows() != n_cols())
    {
        throw std::logic_error("Matrix must be square.");
    }

    auto  n = n_cols();

    // parent[I] is the immediate parent of node I 
    // in the elimination tree.
    idx_vector_type parent  (n, npos);
    idx_vector_type ancestor(n, npos);

    for (idx_type col = 0; col < n; col ++)
    {
        for (idx_type offset = m_col_idx[col]; offset < m_col_idx[col + 1]; offset ++)
        {
            idx_type row  = m_row_idx[offset];

            // Iterate only along the upper-triangular part of A
            if (row >= col)
            {
                break;
            }

            // Walk up the "virtual" forest until you reach the root
            while(ancestor[row] != npos && ancestor[row] != col)
            {
                auto temp     = ancestor[row];
                ancestor[row] = col;
                row           = temp;
            }
            
            if (ancestor[row] == npos)
            {
                ancestor[row] = col;
                parent  [row] = col;
            }
        }
    }
    return parent;
}

#endif
