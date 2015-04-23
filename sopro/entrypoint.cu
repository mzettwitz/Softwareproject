

#include <optix.h>
#include <optixu/optixu_math_namespace.h>

using namespace optix;

rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtBuffer<float4, 2>   result_buffer;

rtDeclareVariable(float4,                color, , );

RT_PROGRAM void drawColor()
{
  result_buffer[launch_index] = color;
}
