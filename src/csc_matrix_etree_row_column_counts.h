//-*-mode: c++-*-
#ifndef _CSC_MATRIX_ETREE_ROW_COLUMN_COUNTS_H_
#define _CSC_MATRIX_ETREE_ROW_COLUMN_COUNTS_H_

template<class idx_type, class el_type>
void csc_matrix<idx_type, el_type>::etree_row_column_counts(idx_vector_type& parent, 
                                                            idx_vector_type& row_counts, 
                                                            idx_vector_type& column_counts) const
{
    parent.resize(m_n_rows);
    row_counts.resize(m_n_rows);
    column_counts.resize(m_n_rows);

    std::fill(parent.begin(), parent.end(), npos);
    std::fill(row_counts.begin(), row_counts.end(), 1);
    std::fill(column_counts.begin(), column_counts.end(), 1);

    idx_vector_type mark(m_n_rows, npos);

    for (auto column = 0; column < m_n_cols; column ++)
    {
        // Mark row 'k' as visited
        mark[column] = column;
        
        for (auto offset = m_col_idx[column]; offset != m_col_idx[column + 1]; offset ++)
        {
            auto row = m_row_idx[offset];
            
            // Only use the upper-triangular part of A
            // I.e., A[i, k] with i < k
            if (row >= column)
            {
                break;
            }

            while (mark[row] != column)
            {
                // Mark row 'i' as visited
                mark[row] = column;

                // A[i, k] != 0 => L[k, i] != 0
                row_counts[column] ++;
                column_counts[row] ++;

                if (parent[row] == npos)
                {
                    parent[row] = column;
                }

                // L[k, i] != 0 and L[j, i] != 0 => L[k, j] != 0
                // Now, parent[i] = j => L[j, i] != 0
                // So, traverse up the elimination tree until
                // you hit the root or a previously visited row
                row = parent[row];                
            }                        
        }        
    }
}

#endif 
