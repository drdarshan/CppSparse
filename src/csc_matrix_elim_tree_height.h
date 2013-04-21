// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_ELIM_TREE_HEIGHT_H_
#define _CSC_MATRIX_ELIM_TREE_HEIGHT_H_

template<class idx_type, class el_type> 
idx_type 
csc_matrix<idx_type, el_type>::elim_tree_height(const typename csc_matrix<idx_type, el_type>::idx_vector_type& parent) const
{
    std::vector<idx_type> height(m_n_rows);

    for (idx_type row = 0; row < m_n_rows; row ++)
    {
        auto par = parent[row];
        auto len = idx_type(0);
        while(par != npos)
        {
            len ++;
            if (height[par] != 0)
            {
                break;
            }
            par = parent[par];
        }
        
        if (par != npos)
        {
            len += height[par];
        }
        
        auto temp = row;
        while (temp != par)
        {
            height[temp] = len;
            len --;
            temp = parent[temp];
        }
    }

    return *std::max_element(height.cbegin(), height.cend());        
}
#endif
