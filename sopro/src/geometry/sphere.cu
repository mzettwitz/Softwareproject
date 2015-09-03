#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <optixu/optixu_aabb_namespace.h>


using namespace optix;

rtDeclareVariable(float3,   coordinates,                ,);
rtDeclareVariable(float,    radius,                     ,);
rtDeclareVariable(Ray,      ray,        rtCurrentRay    ,);
rtDeclareVariable(float3,   geometricNormal, attribute geometricNormal,);
rtDeclareVariable(float3,   shadingNormal, attribute shadingNormal,);


RT_PROGRAM void sphereIntersectionProgram(int primIdx)
{

    //to solve : (o + td - c)² - r² = 0
    // t_1,2 = - (od - dc)/d² +- sqrt(((od-dc)/d²)² - (2oc + o² + c² -r²)/d²

    float3 c        = coordinates;
    float3 o        = ray.origin;
    float3 d        = ray.direction;
    float  r        = radius;

    float  b        = (dot(o,d) - dot(d,c)) / dot(d,d);
    float  e        = (-2 * dot(o,c) + dot(o,o) + dot(c,c) - r*r)/dot(d,d);
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
                float3 normal = -c + o + lambda1 * d;
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
                float3 normal =  -c + o + lambda2 * d;
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

    float3 c = coordinates;
    float3 r = make_float3(radius);

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
