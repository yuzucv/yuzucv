#pragma once
#include <cstdint>
// #include <intrin.h>

// For SSE
#if defined(__SSE2__)
#define SUPPORTS_SSE 1
#else
#define SUPPORTS_SSE 0
#endif

// For AVX and AVX2
#if defined(__AVX__) || (defined(_MSC_VER) && defined(__AVX))
#define SUPPORTS_AVX 1
#else
#define SUPPORTS_AVX 0
#endif

// Check for AVX2
#if defined(__AVX2__) || (defined(_MSC_VER) && defined(__AVX))
#define SUPPORTS_AVX2 1
#else
#define SUPPORTS_AVX2 0
#endif

#if defined(__ARM_NEON)
#define SUPPORTS_NEON 1
#else
#define SUPPORTS_NEON 0
#endif

#if SUPPORTS_SSE && defined(ENABLE_YUZU_SSE)
#define USE_SSE
#include <emmintrin.h>
#endif

#if SUPPORTS_AVX2 && defined(ENABLE_YUZU_AVX2)
#define USE_AVX2
#include <immintrin.h>
#endif

#if SUPPORTS_NEON && defined(ENABLE_YUZU_NEON)
#define USE_NEON
#include <arm_neon.h>
#endif
