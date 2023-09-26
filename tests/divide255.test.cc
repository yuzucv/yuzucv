#include <cstdint>
#include <iostream>

#include "yuzucv/_test.h"
#include "yuzucv/alpha_blending.h"
#include "yuzucv/simd_const.h"

using namespace yuzucv::base;
using namespace _test;

int main()
{
    [[maybe_unused]] constexpr short initValue = 13 * 255;

#ifdef USE_SSE
    const auto initVector1 = 0xcf3_k16;
    auto res1 = sse::divide16By255(initVector1);
    short* y1 = (short*)&res1;
    printArr(y1, 8);
#endif

#ifdef USE_AVX2
    const auto initVector2 = 0xcf3_kk16;
    auto res2 = avx::divide16By255(initVector2);
    short* y2 = (short*)&res2;
    printArr(y2, 16);
#endif
    return 0;
}
