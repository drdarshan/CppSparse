// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_LEAST_COMMON_ANCESTOR_H_
#define _CSC_MATRIX_LEAST_COMMON_ANCESTOR_H_
#include <utility>
template<class idx_type, class el_type>
std::pair<leaf_type, idx_type> csc_matrix<idx_type, el_type>::least_common_ancestor(idx_type               i, 
                                                                                    idx_type               j, 
                                                                                    const idx_vector_type& first_descendent,
                                                                                    idx_vector_type&       ancestor,
                                                                                    idx_vector_type&       maximal_first_descendent,
                                                                                    idx_vector_type&       previous_leaf) const
{    
    auto fdj = first_descendent[j], mfi = maximal_first_descendent[i];

    if (i <= j || (fdj == npos && mfi == npos) || (fdj != npos && mfi != npos && fdj <= mfi))
    {
        return std::make_pair(NOT_LEAF, npos);
    }

    // Update maximal decendent of i
    maximal_first_descendent[i] = first_descendent[j];

    // Let j be the last leaf node of the i-th subtree
    auto prev_leaf   = previous_leaf[i];
    previous_leaf[i] = j;
    
    // If j is the first non-trivial leaf node, i is the LCA
    if (prev_leaf == npos)
    {
        return std::make_pair(FIRST_LEAF, i);
    }

    // Else find LCA(j, prev_leaf)
    auto lca = prev_leaf;
    while(lca != ancestor[lca])
    {
        lca = ancestor[lca];
    }

    // Update path compression
    auto temp = prev_leaf;
    while(temp != lca)
    {
        auto temp2 = ancestor[temp];
        ancestor[temp] = lca;
        temp = temp2;
    }

    return std::make_pair(OTHER_LEAF, lca);
    
}

#endif
