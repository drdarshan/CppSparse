// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_COLUMN_COUNTS_H_
#define _CSC_MATRIX_COLUMN_COUNTS_H_

template<class idx_type, class el_type>
typename csc_matrix<idx_type, el_type>::idx_vector_type 
csc_matrix<idx_type, el_type>::column_counts(const idx_vector_type& parent, 
                                             const idx_vector_type& post_order) const
{
    idx_vector_type first(m_n_rows, npos);
    idx_vector_type max_first(m_n_rows, npos);
    idx_vector_type prev_leaf(m_n_rows, npos);
    idx_vector_type ancestor(m_n_rows);
    idx_vector_type column_count(m_n_rows);

    std::iota(ancestor.begin(), ancestor.end(), 0);

    for (idx_type k = 0; k < m_n_rows; k ++)
    {
        auto j = post_order[k];
        
        if (first[j] == npos)
        {
            column_count[j] = 1;
        }
        else
        {
            column_count[j] = 0;
        }

        while(j != npos && first[j] == npos)
        {
            first[j] = k;
            j        = first[j];
        }
    }

    // Compute the delta factors
    for (idx_type k = 0; k < m_n_rows; k ++)
    {
        auto j = post_order[k];

        for (idx_type offset = m_col_idx[j]; offset < m_col_idx[j + 1]; offset ++)
        {
            auto i = m_row_idx[offset];

            if (i <= j)
            {
                continue;
            }

            auto leaf_type_lca = least_common_ancestor(i, j, first, ancestor, max_first, prev_leaf);
            auto leaf_type     = leaf_type_lca.first;
            auto lca           = leaf_type_lca.second;
            
            if (leaf_type == FIRST_LEAF || leaf_type == OTHER_LEAF)
            {
                column_count[j] ++;
            }

            if (leaf_type == OTHER_LEAF)
            {
                column_count[lca] --;
            }
        }

        if (parent[j] != npos)
        {
            ancestor[j] = parent[j];
        }            
    }

    // Compute the final column counts
    for (idx_type j = 0; j < m_n_rows; j ++)
    {
        if (parent[j] != npos)
        {
            column_count[parent[j]] += column_count[j];
        }
    }

    return column_count;
}

template<class idx_type, class el_type>
typename csc_matrix<idx_type, el_type>::idx_vector_type 
csc_matrix<idx_type, el_type>::column_counts(const idx_vector_type& parent, 
                                             const idx_vector_type& post_order,
                                             bool                   ata_form) const
{
    idx_vector_type column_counts(m_n_rows);
    auto& delta = column_counts;

    return column_counts;
}


#endif
