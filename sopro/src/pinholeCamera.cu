
#include <optix_world.h>
#include "../cuda/helpers.h"
#include "../include/structs.h"

using namespace optix;

//ray from camera to objects, returned payload to buffer

//camera parameters
rtDeclareVariable(float3, eye,,);
rtDeclareVariable(float3,U,,);
rtDeclareVariable(float3,V,,);
rtDeclareVariable(float3,W,,);

//color for exceptions
rtDeclareVariable(float4,exceptionColor,,);
//min distance
rtDeclareVariable(float,sceneEpsilon,,);
//output buffer
rtBuffer<float4,2> outputBuffer;
// 'head' of Scenetree
rtDeclareVariable(rtObject, topObject,,);
//which kind of ray
rtDeclareVariable(unsigned int, radiance_ray_type,,);
//output image size
rtDeclareVariable(uint2, launchIndex, rtLaunchIndex,);
rtDeclareVariable(uint2, launchDim, rtLaunchDim,);


//perspective view
RT_PROGRAM void pinholeCamera()
{
    //setup camera, shift over every pixel
    float2 d = make_float2(launchIndex) / make_float2(launchDim) * 2.f - 1.f;
    float3 rayOrigin = eye;
    float3 rayDirection = normalize(d.x * U + d.y * V + W);

    //create ray
    optix::Ray ray = optix::make_Ray(rayOrigin,rayDirection,radiance_ray_type,sceneEpsilon,RT_DEFAULT_MAX);

    //trace radiance 'normal' rays from camera into scene
    PerRayData_radiance prd;

    prd.importance = 1.f;
    prd.depth = 0;

    rtTrace(topObject, ray, prd);

    //return color to outputBuffer for each pixel
    outputBuffer[launchIndex] = prd.result;
}

//if exception return excpetionColor as payload
RT_PROGRAM void exception()
{
    const unsigned int code = rtGetExceptionCode();
    rtPrintf("Caugt Exception 0x%X at launch index(%d,%d)\n", code, launchIndex.x,launchIndex.y);
    outputBuffer[launchIndex] = exceptionColor;
}
