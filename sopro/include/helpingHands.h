#ifndef HELPINGHANDS_H
#define HELPINGHANDS_H

#include <optixu/optixu_math_namespace.h>

//convert float3 in [0,1)³ to uchar4 [0,255]⁴ , 4th set to 255

#ifdef __CUDACC__
static __device__ __inline__ optix::uchar4 make_color(const optix::float3 &c)
{
    return optix::make_uchar4(static_cast<unsigned char>(__saturatef(c.z)*255.99f), //B
                              static_cast<unsigned char>(__saturatef(c.y)*255.99f), //G
                              static_cast<unsigned char>(__saturatef(c.y)*255.99f), //R
                              255u);                                                //A
}

#endif //__CUDACC_

#endif //HELPINGHANDS_H
