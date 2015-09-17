
/*
 * Copyright (c) 2008 - 2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and proprietary
 * rights in and to this software, related documentation and any modifications thereto.
 * Any use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation is strictly
 * prohibited.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
 * AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
 * SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
 * BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
 * INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES
 */

#include <optix.h>
#include <optixu/optixu_math_namespace.h>

#include "../include/random.h"
#include "../include/structs.h"
#include "../include/helpers.h"

using namespace optix;

rtDeclareVariable(unsigned int,  frameNumber, , );
rtDeclareVariable(float3,        eye, , );
rtDeclareVariable(float3,        U, , );
rtDeclareVariable(float3,        V, , );
rtDeclareVariable(float3,        W, , );
rtDeclareVariable(float3,        exceptionColor, , );
rtDeclareVariable(float,         sceneEpsilon, , );
rtBuffer<uchar4, 2>              outputBuffer;
rtBuffer<float4, 2>              varianceSumBuffer;
rtBuffer<float4, 2>              varianceSum2Buffer;
rtBuffer<unsigned int, 2>        numSamplesBuffer;
rtBuffer<unsigned int, 2>        randomSeeds;
rtDeclareVariable(rtObject,      topObject, , );
rtDeclareVariable(unsigned int,  radianceRayType, , );

rtDeclareVariable(uint2,      launch_index, rtLaunchIndex, );

// Trace ray through screen_coord
static __device__ __inline__ float3 trace( float2 screen_coord )
{
  size_t2 screen = outputBuffer.size();
  float2 d = screen_coord / make_float2(screen) * 2.f - 1.f;
  float3 ray_origin = eye;
  float3 ray_direction = normalize(d.x*U + d.y*V + W);

  optix::Ray ray = optix::make_Ray(ray_origin, ray_direction, radianceRayType, sceneEpsilon, RT_DEFAULT_MAX);

  PerRayData_radiance prd;
  prd.importance = 1.f;
  prd.depth = 0;

  rtTrace(topObject, ray, prd);
  return make_float3(prd.result.x,prd.result.y,prd.result.z);
}


static __device__ __inline__ float3 jittered_trace( const uint2& index )
{
    // Trace a randomly offset ray within the pixel
    volatile unsigned int seed  = randomSeeds[ index ]; // volatile workaround for cuda 2.0 bug
    unsigned int new_seed  = seed;
    float uu = rnd( new_seed )-0.5f;
    float vv = rnd( new_seed )-0.5f;
    randomSeeds[ launch_index ] = new_seed;

    float2 offset = make_float2( uu, vv );
    float3 result = trace( offset + make_float2( index ) );

    return result;
}

RT_PROGRAM void pinholeCamera()
{
  if ( frameNumber == 0 ) {
    float3 result = jittered_trace( launch_index );
    outputBuffer[ launch_index ] = make_color( result );

    // Update buffers
    numSamplesBuffer[ launch_index ]   = 1u;
    varianceSumBuffer[ launch_index ]  = make_float4(result, 0.0f);
    varianceSum2Buffer[ launch_index ] = make_float4(result*result, 0.0f);
  } else {
    {
      // ns < 0x80000000 means the variance is too high and we should keep rendering.
      volatile unsigned int ns = numSamplesBuffer[ launch_index ];
      if ( (ns & 0x80000000) && (((launch_index.y >> 3) & 0x3) != (frameNumber & 0x3)) ) {
        return;
      }
    }

    float3 new_color = jittered_trace( launch_index );

    // Add in new ray's contribution
    volatile unsigned int ns = numSamplesBuffer[ launch_index ] & ~0x80000000; // volatile workaround for Cuda 2.0 bug
    float  new_value_weight = 1.0f / (float)ns;
    float  old_value_weight = 1.0f - new_value_weight;
    uchar4& old_bytes = outputBuffer[ launch_index ];
    float3 old_color = make_float3(old_bytes.z, old_bytes.y, old_bytes.x)*make_float3(1.f/255.0f);
    float3 result = old_color*old_value_weight + new_color*new_value_weight;

    // Update buffers
    outputBuffer[ launch_index ] = make_color(result);
    float4 vsum  = varianceSumBuffer[ launch_index ];
    float4 vsum2 = varianceSum2Buffer[ launch_index ];
    // Compute the variance of the series of displayed pixels over time. This variance will go to zero, regardless of the variance of the sample values.
    varianceSumBuffer[ launch_index ]  = vsum  = vsum  + make_float4( result, 0.0f );
    varianceSum2Buffer[ launch_index ] = vsum2 = vsum2 + make_float4( result*result, 0.0f );
    ns++;

    // If we are beyond our first four samples per pixel, check variance
    if ( frameNumber > 6 ) {
      float3 rgb_variance = ( make_float3( vsum2 ) - make_float3( vsum ) * make_float3( vsum ) * new_value_weight ) * new_value_weight;

      float variance = optix::luminance( rgb_variance );
      // render an 8-row span every 32 rows regardless. This shape lets entire warps turn off.
      if ( variance < 0.001f ) {
        ns = ns | 0x80000000;
      }
    }

    numSamplesBuffer[ launch_index ] = ns;
  }
}


RT_PROGRAM void exception()
{
  const unsigned int code = rtGetExceptionCode();
  rtPrintf( "Caught exception 0x%X at launch index (%d,%d)\n", code, launch_index.x, launch_index.y );
  outputBuffer[launch_index] = make_color(exceptionColor);
}
