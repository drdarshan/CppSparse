// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_EREACH2_H_
#define _CSC_MATRIX_EREACH2_H_

template<class idx_type, class el_type>
void csc_matrix<idx_type, el_type>::ereach2(const idx_vector_type& parent, idx_type col, std::vector<bool>& marked, idx_vector_type& reach) const
{
    reach.reserve(m_n_cols);

    // Ensure that you always hit node J when traversing 
    // up the elimination tree
    marked[col] = true;
    for (idx_type offset = m_col_idx[col]; offset < m_col_idx[col + 1]; offset ++)
    {        
        idx_type row = m_row_idx[offset];

        // Only the upper-triangular part of A is needed
        if (row >= col)
        {
            break;
        }

        // Traverse up the elimination tree until you hit a marked
        // node
        while(!marked[row])
        {
            reach.push_back(row);
            marked[row] = true;
            row         = parent[row];
        }        
    }

    // Unmark the work array
    std::for_each(reach.cbegin(), reach.cend(), [&marked](idx_type row) {marked[row] = false;});
}

template<class idx_type, class el_type>
typename csc_matrix<idx_type, el_type>::idx_vector_type 
csc_matrix<idx_type, el_type>::ereach2(const idx_vector_type& parent, idx_type col) const
{
    std::vector<bool> mark(m_n_cols);
    idx_vector_type reach;
    ereach2(parent, col, mark, reach);
    return reach;
}
#endif

