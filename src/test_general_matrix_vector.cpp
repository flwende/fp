// Copyright (c) 2017-2018 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <omp.h>
#include <general_matrix_vector_kernel.hpp>

constexpr std::size_t m_default = 256;
constexpr std::size_t n_default = 256;
constexpr std::size_t num_matrices_default = 100;
constexpr std::size_t bs_default = 32;

#if defined(BENCHMARK)
constexpr std::size_t warmup = 5;
constexpr std::size_t measurement = 10;
#else
constexpr std::size_t warmup = 0;
constexpr std::size_t measurement = 1;
#endif

void kernel(const real_t alpha, const real_t beta, const bool transpose,
    const std::size_t m, const std::size_t n,
    const std::vector<std::vector<real_t>>& a,
    const std::vector<fp_matrix>& a_compressed,
    const std::vector<std::vector<real_t>>& x,
    std::vector<std::vector<real_t>>& y_ref,
    std::vector<std::vector<real_t>>& y,
    const bool use_blas = false);

int main(int argc, char** argv)
{
    // read command line arguments
    const std::size_t m = (argc > 1 ? atoi(argv[1]) : m_default);
    const std::size_t n = (argc > 2 ? atoi(argv[2]) : n_default);
    const std::size_t num_matrices = (argc > 3 ? atoi(argv[3]) : num_matrices_default);
    const std::size_t bs = (argc > 4 ? atoi(argv[4]) : bs_default);
    const bool use_blas = (argc > 5 ? (atoi(argv[5]) != 0 ? true : false) : false);

    std::cout << "matrix multiply: " << m << " x " << n << std::endl;
    std::cout << "num matrices: " << num_matrices << std::endl;

    // create matrices and vectors
    std::vector<std::vector<real_t>> a(num_matrices), x(num_matrices), y_ref(num_matrices), y(num_matrices);
    std::vector<fp_matrix> a_compressed;
    a_compressed.reserve(num_matrices);
    for (std::size_t k = 0; k < num_matrices; ++k)
    {
        a[k].reserve(m * n);
        srand48(k + 1);
        for (std::size_t i = 0; i < (m * n); ++i)
        {
            a[k][i] = 0.9 + 0.2 * drand48();
        }

        x[k].reserve(n);
        for (std::size_t i = 0; i < n; ++i)
        {
            x[k][i] = 0.9 + 0.2 * drand48();
        }

        a_compressed.emplace_back(a[k], m, n, bs);

        y_ref[k].reserve(m);
        y[k].reserve(m);
        for (std::size_t i = 0; i < m; ++i)
        {
            y_ref[k][i] = 0.0;
            y[k][i] = 0.0;
        }
    }

    #if defined(BENCHMARK)
    // parameters for the matrix vector multiplication
    const real_t alpha = static_cast<real_t>(1.0);
    const real_t beta = static_cast<real_t>(0.0);
    const bool transpose = true;

    kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
    #else
    {
        const real_t alpha = static_cast<real_t>(1.0);
        const real_t beta = static_cast<real_t>(0.0);
        const bool transpose = false;
        kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        if (m == n)
        {
            const bool transpose = true;
            kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        }
    }
    {
        const real_t alpha = static_cast<real_t>(-1.1);
        const real_t beta = static_cast<real_t>(0.0);
        const bool transpose = false;
        kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        if (m == n)
        {
            const bool transpose = true;
            kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        }
    }
    {
        const real_t alpha = static_cast<real_t>(0.0);
        const real_t beta = static_cast<real_t>(-0.5);
        const bool transpose = false;
        kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        if (m == n)
        {
            const bool transpose = true;
            kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        }
    }
    {
        const real_t alpha = static_cast<real_t>(0.0);
        const real_t beta = static_cast<real_t>(0.0);
        const bool transpose = false;
        kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        if (m == n)
        {
            const bool transpose = true;
            kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        }
    }
    {
        const real_t alpha = static_cast<real_t>(2.3);
        const real_t beta = static_cast<real_t>(0.0);
        const bool transpose = false;
        kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        if (m == n)
        {
            const bool transpose = true;
            kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        }
    }
    {
        const real_t alpha = static_cast<real_t>(-0.34);
        const real_t beta = static_cast<real_t>(1.1);
        const bool transpose = false;
        kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        if (m == n)
        {
            const bool transpose = true;
            kernel(alpha, beta, transpose, m, n, a, a_compressed, x, y_ref, y, use_blas);
        }
    }
    #endif
    
    return 0;
}

void kernel(const real_t alpha, const real_t beta, const bool transpose,
    const std::size_t m, const std::size_t n,
    const std::vector<std::vector<real_t>>& a,
    const std::vector<fp_matrix>& a_compressed,
    const std::vector<std::vector<real_t>>& x,
    std::vector<std::vector<real_t>>& y_ref,
    std::vector<std::vector<real_t>>& y,
    const bool use_blas)
{
    // print some information
    std::cout << "alpha: " << alpha << ", beta: " << beta << ", transpose: " << (transpose ? "true" : "false") << std::endl;

    // reference computation
    for (std::size_t k = 0; k < a.size(); ++k)
    {
        blas_matrix_vector(transpose, m, n, alpha, a[k], x[k], beta, y_ref[k]);
    }

    if (use_blas)
    {
        std::cout << "mode: standard blas (matrix memory consumption: " << a.size() * n * m * sizeof(real_t) / (1024 * 1024) << " MiB)" << std::endl;
    }
    else
    {
        std::cout << "mode: fp_matrix, BE = " << BE << ", BM = " << BM << " (matrix memory consumption: " << a.size() * a_compressed[0].memory_footprint_bytes() / (1024 * 1024) << " MiB)" << std::endl;
    }

    // own implementation
    double time_start = 0.0;
    double time_stop = 0.0;

    #pragma omp parallel
    {
        for (std::size_t l = 0; l < warmup; ++l)
        {
            if (use_blas)
            {
                #pragma omp for
                for (std::size_t k = 0; k < a.size(); ++k)
                {
                    blas_matrix_vector(transpose, m, n, alpha, a[k], x[k], beta, y[k]);
                }
            }
            else
            {
                #pragma omp for
                for (std::size_t k = 0; k < a.size(); ++k)
                {
                    fp_matrix_vector(transpose, alpha, a_compressed[k], x[k], beta, y[k]);
                }
            }
        }

        #pragma omp barrier
        #pragma omp master
        {
            time_start = omp_get_wtime();
        }
        #pragma omp barrier

        //time_start = omp_get_wtime();
        for (std::size_t l = 0; l < measurement; ++l)
        {
            if (use_blas)
            {
                #pragma omp for
                for (std::size_t k = 0; k < a.size(); ++k)
                {
                    blas_matrix_vector(transpose, m, n, alpha, a[k], x[k], beta, y[k]);
                }
            }
            else
            {
                #pragma omp for
                for (std::size_t k = 0; k < a.size(); ++k)
                {
                    fp_matrix_vector(transpose, alpha, a_compressed[k], x[k], beta, y[k]);
                }
            }

        }

        #pragma omp barrier
        #pragma omp master
        {
            time_stop = omp_get_wtime();
        }
    }

    #if defined(BENCHMARK)
    // output some metrics
    const double gflops = measurement * (a.size() * 2 * m * n) / (time_stop - time_start) * 1.0E-9;
    std::cout << "gflops: " << gflops << std::endl;
    #else
    // correctness
    double dev = 0.0;
    real_t v_1 = y_ref[0][0];
    real_t v_2 = y[0][0];
    for (std::size_t k = 0; k < a.size(); ++k)
    {
        for (std::size_t i = 0; i < m; ++i)
        {
            const double tmp = std::abs((y[k][i] - y_ref[k][i]) / y_ref[k][i]);
            if (tmp > dev)
            {
                dev = tmp;
                v_1 = y_ref[k][i];
                v_2 = y[k][i];
            }
        }
    }
    std::cout << "deviation: " << dev << " (" << v_1 << " vs. " << v_2 << ")" << std::endl;
    #endif
}