#pragma once
#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <type_traits>

namespace _test
{
template <typename T>
void printArr(T* ptr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        if constexpr (std::is_arithmetic_v<T> && sizeof(T) == 1)
        {
            std::cout << (int)ptr[i] << " ";
        }
        else
        {
            std::cout << ptr[i] << " ";
        }
    }
    std::cout << "\n";
}

template <typename... T>
void print(T&&... args)
{
    if constexpr (sizeof...(args) > 0)
    {
        ((std::cout << args << " "), ...);
    }
    std::cout << "\n";
}

template <int N>
std::array<float, N> newTensor()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist;
    std::array<float, N> tensor;
    for (int i = 0; i < N; i++)
    {
        tensor[i] = dist(gen);
    }
    return tensor;
};

template <int N, class T>
std::array<T, N> newArray()
{
    static_assert(std::is_arithmetic_v<T>, "must be a number type");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist;
    std::array<T, N> tensor;

    T a = std::numeric_limits<T>::min();
    T b = std::numeric_limits<T>::max();
    for (int i = 0; i < N; i++)
    {
        tensor[i] = a + static_cast<T>(dist(gen) * (b - a));
    }
    return tensor;
};
} // namespace _test