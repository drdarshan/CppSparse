// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_FIRST_DESCENDENT_H_
#define _CSC_MATRIX_FIRST_DESCENDENT_H_
#include <utility>
template<class idx_type, class el_type>
std::pair<typename csc_matrix<idx_type, el_type>::idx_vector_type, 
          typename csc_matrix<idx_type, el_type>::idx_vector_type> 
csc_matrix<idx_type, el_type>::first_descendent(const idx_vector_type& parent, const idx_vector_type& post_order) const
{
    idx_vector_type first_descendent;
    idx_vector_type level;
    
    this->first_descendent(parent, post_order, first_descendent, level);
    
    return std::make_pair(first_descendent, level);
}

template<class idx_type, class el_type>
void
csc_matrix<idx_type, el_type>::first_descendent(const idx_vector_type& parent, 
                                                const idx_vector_type& post_order, 
                                                idx_vector_type& first_descendent, 
                                                idx_vector_type& level) const
{
    first_descendent.resize(m_n_rows);
    level.resize(m_n_rows);
    
    std::fill(first_descendent.begin(), first_descendent.end(), npos);
    std::fill(level.begin(), level.end(), 0);

    for (idx_type k = 0; k < m_n_rows; k ++)
    {
        idx_type i      = post_order[k];

        idx_type temp1  = i;
        idx_type length = 0;

        // Walk up the tree until you either hit a previously
        // visited node or the root
        while(parent[temp1] != npos && first_descendent[temp1] == npos)
        {
            length ++;
            first_descendent[temp1] = k;
            temp1                   = parent[temp1];
        }

        // Adjust the descendent of the root
        if (parent[temp1] == npos && first_descendent[temp1] == npos)
        {
            first_descendent[temp1] = k;
        }
        // Or the length of the current node from the root
        else
        {
            length += level[temp1];
        }

        // Set the level of all the nodes on the path
        // from 'i' to the root of the tree
        auto temp2 = i;
        while(temp2 != temp1)
        {
            level[temp2] = length;
            length --;
            temp2 = parent[temp2];
        }
    }
}


#endif
