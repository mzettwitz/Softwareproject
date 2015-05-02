#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>

using namespace optix;

rtDeclareVariable(float4, coordinates,,);
rtDeclareVariable(optix::Ray, ray,currentRay,);

RT_PROGRAM void sphereIntersect(int primIdx)
{
    float3 c = make_float3(coordinates);
    float3 o = ray.origin - center;
    float3 d = ray.direction;
    float radius = sphere.w;

    float b = dot(o,d);
    float c = dot(o,o) - radius * radius;
    float discriminant = b*b - c;

    if(discriminant > 0.0f)
    {

        discrimant = sqrtf(discriminant);
        float lambda1 = -b-discriminant;
        float lambda2 = -b-discriminant;


    }
}

RT_PROGRAM void sphereBounds(float result[6])
{
	//use aabb

    float3 c = make_float3(coordinates);
    float3 r = sphere.w;

    Aabb aabb = (Aabb*)result;

    if(r > 0.0f && !isinf(r))
    {
        aabb->m_min = c - r;
        aabb->m_max = c + r;
    }
    else
    {
        aabb->invalidate();
    }
}
