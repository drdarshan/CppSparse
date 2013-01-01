// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_ROW_COUNTS_H_
#define _CSC_MATRIX_ROW_COUNTS_H_

template<class idx_type, class el_type>
typename csc_matrix<idx_type, el_type>::idx_vector_type 
csc_matrix<idx_type, el_type>::row_counts(const idx_vector_type& parent, 
                                          const idx_vector_type& post_order) const
{
    idx_vector_type descendent(m_n_rows); 
    idx_vector_type level(m_n_rows);
    idx_vector_type maximum_first_descendent(m_n_rows, npos);
    idx_vector_type previous_leaf(m_n_rows, npos);
    idx_vector_type ancestor(m_n_rows); 
    idx_vector_type row_count(m_n_rows, 1);

    first_descendent(parent, post_order, descendent, level);

    std::iota(ancestor.begin(), ancestor.end(), 0);

    for (idx_type k = 0; k < m_n_rows; k ++)
    {
        auto j = post_order[k];

        for(auto offset = m_col_idx[j]; offset < m_col_idx[j + 1]; offset++)
        {
            auto i = m_row_idx[offset];

            if (i <= j)
            {
                continue;
            }

            auto lca_leaf_type = least_common_ancestor(i, 
                                                       j, 
                                                       descendent,    
                                                       ancestor, 
                                                       maximum_first_descendent, previous_leaf);

            if (lca_leaf_type.first == FIRST_LEAF || lca_leaf_type.first == OTHER_LEAF)
            {
                row_count[i] += (level[j] - level[lca_leaf_type.second]);
            }
        }
        
        if (parent[j] != npos)
        {
            ancestor[j] = parent[j];
        }        
    }

    return row_count;
}

#endif
