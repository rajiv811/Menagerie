/**
 * @file TimeIt.h - 
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include <stdexcept>
#include <random>
#include <chrono>

template <typename Sorter>
class SortTimer {
public:
    static double timeit(size_t n, int repeats=1) {
        std::uniform_real_distribution<double> distribution(-1e100, 1e100);
        std::random_device rd;
        std::mt19937 generator(rd());
        double *a = new double[n];
        double *b = new double[n];
        for (size_t i = 0; i < n; i++)
            b[i] = distribution(generator);

        Sorter sorter(a, n);
        auto start = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = start - start;
        for (int i = 0; i < repeats; i++) {
            start = std::chrono::system_clock::now();
            for (size_t i = 0; i < n; i++)
                a[i] = b[i];
            sorter.sort();
            auto end = std::chrono::system_clock::now();
            elapsed_seconds += end - start;
        }

        check(a, n);
        delete[] a;
        return elapsed_seconds.count();
    }

    static void check(double *a, size_t n) {
        for (size_t i = 1; i < n; i++)
            if (a[i] < a[i-1])
                throw std::logic_error("sort failed!");
    }
};
