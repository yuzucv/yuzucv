#include <cstdint>
#include <immintrin.h>
#include <iostream>

#include "yuzucv/_test.h"
#include "yuzucv/alpha_blending.h"
#include "yuzucv/simd_const.h"

using namespace yuzucv::base;
using namespace _test;

int main()
{
    [[maybe_unused]] constexpr short initValue = 13 * 255;
    const auto initVector1 = 0xcf3_k16;
    const auto initVector2 = 0xcf3_kk16;

    auto res1 = sse::divide16By255(initVector1);
    auto res2 = avx::divide16By255(initVector2);

    short* y1 = (short*)&res1;
    short* y2 = (short*)&res2;

    printArr(y1, 8);
    printArr(y2, 16);

    return 0;
}
