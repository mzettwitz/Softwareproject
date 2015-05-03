#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>

using namespace optix;

rtDeclareVariable(float4, coordinates,,);
rtDeclareVariable(optix::Ray, ray,rtCurrentRay,);

RT_PROGRAM void sphereIntersect(int primIdx)
{
    float3 c = make_float3(coordinates);
    float3 o = ray.origin - c;
    float3 d = ray.direction;
    float radius = coordinates.w;

    float b = dot(o,d);
    float e = dot(o,o) - radius * radius;
    float discriminant = b*b - e;

    if(discriminant > 0.0f)
    {

        discriminant = sqrtf(discriminant);
        float lambda1 = -b-discriminant;
        float lambda2 = -b-discriminant;

        if(lambda1 < lambda2)
        {
            if(rtPotentialIntersection(lambda1))
            {
                rtReportIntersection(0);
            }
        }
        else
        {
            if(rtPotentialIntersection(lambda2))
            {
                    rtReportIntersection(0);
            }
        }
    }
}

RT_PROGRAM void sphereBounds(int,float result[6])
{
	//use aabb

    float3 c = make_float3(coordinates);
    float3 r = make_float3(coordinates.w);

    Aabb* aabb = (Aabb*)result;

    if(r.x > 0.0f && !isinf(r.x))
    {
        aabb->m_min = c - r;
        aabb->m_max = c + r;
    }
    else
    {
        aabb->invalidate();
    }
}
