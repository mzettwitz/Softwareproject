#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>


using namespace optix;

rtDeclareVariable(float4, coordinates,,);
rtDeclareVariable(Ray, ray,rtCurrentRay,);

RT_PROGRAM void sphereIntersectionProgram(int primIdx)
{

    //to solve : (o + td - c)² - r² = 0
    // t_1,2 = - (od - dc)/d² +- sqrt(((od-dc)/d²)² - (2oc + o² + c² -r²)/d²

    float3 c = make_float3(coordinates);
    float3 o = ray.origin;
    float3 d = ray.direction;
    float r = coordinates.w;

    float b = (dot(o,d) - dot(d,c)) / dot(d,d);
    float e = (-2 * dot(o,c) + dot(o,o) + dot(c,c) - r*r)/dot(d,d);
    float discriminant = b*b - e;

    if(discriminant >= 0.0f)
    {

        discriminant = sqrtf(discriminant);
        float lambda1 = -b-discriminant;
        float lambda2 = -b+discriminant;

        if(lambda1 < lambda2 && lambda1 > 0.0f)
        {
            if(rtPotentialIntersection(lambda1))
            {
                rtReportIntersection(0);
            }
        }
        else
        {
            if(lambda2 > 0.0f)
            {
               if(rtPotentialIntersection(lambda2))
               {
                    rtReportIntersection(0);
               }
            }
        }
    }
}

RT_PROGRAM void sphereBoundingBoxProgram(int,float result[6])
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