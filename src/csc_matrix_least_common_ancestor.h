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
                                                                                    idx_type&              previous_leaf) const
{
    return std::make_pair(NOT_LEAF, npos);
}

#endif
