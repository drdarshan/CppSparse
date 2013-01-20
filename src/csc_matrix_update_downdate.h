// -*- mode: c++ -*-
#ifndef _CSC_MATRIX_UPDATE_DOWNDATE_H_
#define _CSC_MATRIX_UPDATE_DOWNDATE_H_

template<class idx_type, class el_type>
csc_matrix<idx_type, el_type> csc_matrix<idx_type, el_type>::update_downdate(const csc_matrix<idx_type, el_type>& w_sparse,
                                                                             const idx_vector_type&               parent, 
                                                                             bool                                 update)
{
    std::vector<el_type> w(m_n_rows);
    w_sparse.scatter(0, w);

    auto j = w_sparse.m_row_idx[0];

    auto beta  = static_cast<el_type> (1);
    auto sigma = static_cast<el_type> (update ? 1 : -1);

    while (j != npos)
    {
        auto offset = m_col_idx[j];
     
        // alpha = W[j] / L[j, j]
        auto alpha = w[j] / m_x[offset];

        auto beta2 = beta * beta + sigma * alpha * alpha;

        if (beta2 < 0)
        {
            throw std::runtime_error("Not positive definite.");
        }

        beta2 = sqrt(beta2);

        auto delta = update ? (beta/beta2) : (beta2/beta);
        
        auto gamma = sigma * alpha / (beta2 * beta);

        // L[j,j]   = delta * L[j,j]      + gamma * W[j]  if update
        //          = delta * L[j,j]                      if downdate
        m_x[offset] = delta * m_x[offset] + (update ? (gamma * w[j]) : 0);

        offset ++;
        while (offset != m_col_idx[j + 1])
        {
            auto w1 = w[m_row_idx[offset]];
            auto w2 = w1 - alpha * m_x[offset];
            w[m_row_idx[offset]] = w2;
            m_x[offset] = delta * m_x[offset] + gamma * (update ? w1 : w2);
            offset ++;
        }

        // Prepare for next iteration
        beta = beta2;
        j    = parent[j];
    }
    return *this;
}

#endif
