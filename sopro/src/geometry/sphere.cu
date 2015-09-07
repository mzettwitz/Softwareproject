#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>


using namespace optix;

rtDeclareVariable(Ray,      ray,        rtCurrentRay    ,);
rtDeclareVariable(float3,   geometricNormal, attribute geometricNormal,);
rtDeclareVariable(float3,   shadingNormal, attribute shadingNormal,);


RT_PROGRAM void sphereIntersectionProgram(int primIdx)
{

    //to solve : (o + td)² - 1 = 0
    // t_1,2 = - (od)/d² +- sqrt(((od)/d²)² - (o²-1)/d²
    float3 o        = ray.origin;
    float3 d        = ray.direction;

    float  b        = (dot(o,d)) / dot(d,d);
    float  e        = (dot(o,o) - 1)/dot(d,d);
    float  disc     = b*b - e;

    if(disc >= 0.0f)
    {
        disc = sqrtf(disc);
        float lambda1 = -b-disc;
        float lambda2 = -b+disc;

        if(lambda1 < lambda2 && lambda1 > 0.0f)
        {
            if(rtPotentialIntersection(lambda1))
            {
                float3 normal = o + lambda1 * d;
                normal = normalize(normal);
                geometricNormal = normal;
                shadingNormal = normal;
                rtReportIntersection(0);
            }
        }
        else
        {
            if(rtPotentialIntersection(lambda2))
            {
                float3 normal = o + lambda2 * d;
                normal = normalize(normal);
                geometricNormal = normal;
                shadingNormal = normal;
                rtReportIntersection(0);
            }
        }
    }
}

RT_PROGRAM void sphereBoundingBoxProgram(int,float result[6])
{
    //use aabb(axis aligned bounding box)
    //just set min and max coordinates

    Aabb* aabb = (Aabb*)result;
        aabb->m_min = make_float3(-1);
        aabb->m_max = make_float3(1);
}
