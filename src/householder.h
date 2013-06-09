
#ifndef _HOUSEHOLDER_H_
#define _HOUSEHOLDER_H_
#include<vector>
#include<tuple>
#include <iostream>
template<class el_type>
std::vector<el_type> householder(std::vector<el_type>& vec)
{
    el_type norm;
    el_type beta;

    auto sigma = std::accumulate(vec.begin() + 1, vec.end(), 0.0, [](el_type left, el_type right) {return left + (right * right);});
    if (sigma == el_type(0))
    {
        norm = std::abs(vec[0]);
        beta = (vec[0] <= 0) ? 2 : 0;
        vec[0] = 1;
    }
    else
    {
        norm = sqrt(vec[0] * vec[0] + sigma);
        auto temp = (vec[0] <= 0) ? (vec[0] - norm) : (-sigma / (vec[0] + norm));
        beta = -1/(norm * temp);
        vec[0] = temp;
    }
    std::vector<el_type> result;
    result.push_back(norm);
    result.push_back(beta);
    return result;
}
#endif
