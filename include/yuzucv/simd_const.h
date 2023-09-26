#pragma once
#include "simd_def.h"

#ifdef USE_SSE
inline __m128i operator"" _k8(unsigned long long x) { return _mm_set1_epi8(x); }
inline __m128i operator"" _k16(unsigned long long x) { return _mm_set1_epi16(x); }
inline __m128i operator"" _k32(unsigned long long x) { return _mm_set1_epi32(x); }
#endif

#ifdef USE_AVX2
inline __m256i operator"" _kk8(unsigned long long x) { return _mm256_set1_epi8(x); }
inline __m256i operator"" _kk16(unsigned long long x) { return _mm256_set1_epi16(x); }
inline __m256i operator"" _kk32(unsigned long long x) { return _mm256_set1_epi32(x); }
#endif