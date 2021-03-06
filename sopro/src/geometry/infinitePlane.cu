#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>

using namespace optix;

rtDeclareVariable(float3,plane,,);
rtDeclareVariable(Ray,ray,rtCurrentRay,);
rtDeclareVariable(float,sceneEpsilon,,);
rtDeclareVariable(float3, geometricNormal, attribute geometricNormal,);
rtDeclareVariable(float3, shadingNormal, attribute shadingNormal,);
RT_PROGRAM void infinitePlaneIntersectionProgram(int primIdx)
{
    float t = 0;
    if( t = (-ray.origin.y + plane.y) / ray.direction.y)
    {
        if(rtPotentialIntersection(t))
        {
            geometricNormal = make_float3(0.0f,1.0f,0.0f);
            shadingNormal = make_float3(0.0f,1.0f,0.0f);
            rtReportIntersection(0);
        }
    }
}

RT_PROGRAM void infinitePlaneBoundingBoxProgram(int primIdx, float result[6])
{
    result[0] = plane.x;
    result[1] = plane.y - plane.x;
    result[2] = plane.x;
    result[3] = plane.z;
    result[4] = plane.y + plane.x;
    result[5] = plane.z;
}
