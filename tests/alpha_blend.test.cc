#include <cstdio>

#include "yuzucv/alpha_blending.h"

using namespace yuzucv;
using namespace yuzucv::base;

int main()
{
    unsigned char sourceColor[4] = {255, 0, 0, 128};      // Red with 50% opacity
    unsigned char destinationColor[4] = {0, 0, 255, 255}; // Blue with 100% opacity
    float alpha = 0.5;                                    // Alpha value (0.0 to 1.0)

    alphaPremultiply_s(sourceColor, sourceColor);

    auto resultColor = sourceColor;
    printf("Result Color (R, G, B, A): %d, %d, %d, %d\n", resultColor[0], resultColor[1], resultColor[2],
           resultColor[3]);

    return 0;
}