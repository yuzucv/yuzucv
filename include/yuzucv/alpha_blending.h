#pragma once
#include <cstdint>
#include <immintrin.h>

#include "simd_def.h"

namespace yuzucv
{
namespace internal
{
inline int divideBy255(int value) { return (value + 1 + (value >> 8)) >> 8; }
} // namespace internal

namespace base
{
/**
 * @brief Perform alpha blending for a colors
 *
 * @tparam rgba (A, R, G, B)
 * @param src source 4 pixel
 * @param dst destination 4 pixel
 */
template <bool rgba = true>
void alphaPremultiply_s(const uint8_t* src, uint8_t* dst);

template <>
inline void alphaPremultiply_s<true>(const uint8_t* src, uint8_t* dst)
{
    // rgb a
    int alpha = src[3];
    dst[0] = internal::divideBy255(src[0] * alpha);
    dst[1] = internal::divideBy255(src[1] * alpha);
    dst[2] = internal::divideBy255(src[2] * alpha);
    dst[3] = alpha;
}

template <>
inline void alphaPremultiply_s<false>(const uint8_t* src, uint8_t* dst)
{
    // a rgb
    int alpha = src[0];
    dst[1] = internal::divideBy255(src[1] * alpha);
    dst[2] = internal::divideBy255(src[2] * alpha);
    dst[3] = internal::divideBy255(src[3] * alpha);
    dst[0] = alpha;
}

#ifdef USE_AVX2
namespace avx
{
} // namespace avx

#endif

} // namespace base

} // namespace yuzucv