// Copyright (c) 2017-2018 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#include <general_matrix_vector_kernel.hpp>
#include <omp.h>

#include "general_matrix_vector_kernel_blas.cpp"

double fp_matrix_vector(const bool transpose, const mat_t alpha, const fp_matrix& a, const std::vector<vec_t>& x, const vec_t beta, std::vector<vec_t>& y)
{
    double time = omp_get_wtime();
    {
        a.matrix_vector(transpose, alpha, x, beta, y);
    }
    return (omp_get_wtime() - time);
}