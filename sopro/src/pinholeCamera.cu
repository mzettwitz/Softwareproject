#include <optix_world.h>

using namespace optix;

//ray from camera to objects
struct PerRayData_radiance
{
    //color
    float4 result;
    //not used now
    float importance;
    //recursion depth
    int depth;
};


//camera parameters
rtDeclareVariable(float3, eye,,);
rtDeclareVariable(float3,U,,);
rtDeclareVariable(float3,V,,);
rtDeclareVariable(float3,W,,);


rtDeclareVariable(float3,exceptionColor,,);
rtDeclareVariable(float,sceneEpsilon,,);
rtBuffer<float3,2> output_buffer;
rtDeclareVariable(rtObject, topObject,,);
rtDeclareVariable(unsigned int, radiance_ray_type,,);

rtDeclareVariable(uint2, launchIndex, rtLauchindex,);
rtDeclareVariable(uint2, launchDim, rtLaunchDim,);



RT_PROGRAM void pinholeCamera()
{
    float2 d = make_float2(launchIndex) / make_float2(launchDim) * 2.f - 1.f;
    float3 rayOrigin = eye;
    float3 rayDirection = normalize(d.x * U, d.y * V + W);

    optix::Ray ray = optix::make_Ray(rayOrigin,rayDirection,radiance_ray_type,sceneEpsilon,RT_DEFAULT_MAX);

    PerRayData_radiance prd;

    prd.importance = 1.f;
    prd.depth = 0;

    rtTrace(topObject, ray, prd);

    output_buffer[launchIndex] = make_color(prd.result);
}


RT_PROGRAM void exception()
{
    const unsigned int code = rtGetExceptionCode();
    rtPrintf("Caugt Exception 0x%X at launch index(%d,%d)\n", code, launchIndex.x,launchIndex.y);
    output_buffer[launchIndex] = make_color(exceptionColor);
}
