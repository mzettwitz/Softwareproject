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
rtDeclareVariable(float4, eye,,);
rtDeclareVariable(float4,U,,);
rtDeclareVariable(float4,V,,);
rtDeclareVariable(float4,W,,);


rtDeclareVariable(float4,exceptionColor,,);
rtDeclareVariable(float,sceneEpsilon,,);
rtBuffer<float4,2> output_buffer;
