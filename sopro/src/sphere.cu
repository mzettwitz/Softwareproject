#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>

using namespace optix;

rtDeclareVariable(float3, sphereMin,,);
rtDeclareVariable(float3, sphereMax,,);
rtDeclareVariable(optix::Ray, ray,currentRay,);
rtDeclareVariable(float3,geometricNormal, attribute geometric_normal,);
rtDeclareVariable(float3,shadingNormal, attribute shading_normal,);

RT_PROGRAM void sphereIntersect(int)
{
	//solve quadratic equation
}

RT_PROGRAM void sphereBounds(int, float center, float radius)
{
	//use aabb
}
