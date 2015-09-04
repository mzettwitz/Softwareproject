#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>

using namespace optix;

rtDeclareVariable(float3, position,,);
rtDeclareVariable(float3,dimensions,,);
rtDeclareVariable(Ray,ray,rtCurrentRay,);
rtDeclareVariable(float,sceneEpsilon,,);
rtDeclareVariable(float3, geometricNormal, attribute geometricNormal,);
rtDeclareVariable(float3, shadingNormal, attribute shadingNormal,);


RT_PROGRAM void areaPlaneIntersectionProgram(int primIdx)
{

}


RT_PROGRAM void areaPlaneBoundingBoxProgram(int primIdx, float result[6])
{

}
