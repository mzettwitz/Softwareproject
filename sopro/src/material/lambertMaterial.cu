
#include "../../include/structs.h"

#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>

using namespace optix;

rtDeclareVariable(PerRayData_radiance,prd_radiance,rtPayload,);
rtDeclareVariable(PerRayData_shadow,prd_shadow,rtPayload,);
rtDeclareVariable(optix::Ray, ray, rtCurrentRay,);
rtDeclareVariable(unsigned int, shadowRayType,,);
rtDeclareVariable(unsigned int, radianceRayType,,);
rtDeclareVariable(float, sceneEpsilon,,);
rtDeclareVariable(rtObject, topShadower,,);
rtBuffer<PointLight> lights;
rtDeclareVariable(float, intersectionDistance, rtIntersectionDistance,);
rtDeclareVariable(float3,color,,);
rtDeclareVariable(float3, normal, attribute normal,);

static __device__ void shadowed();
static __device__ void shade();

RT_PROGRAM void anyhit_shadow()
{
    shadowed();
}

RT_PROGRAM void closesthit_radiance()
{
    shade();
}


/*! \fn shadowed
 * \brief method to generate a shadow
 *
 * Generate a new shadow ray if a the incoming ray hits an object
 */

static __device__ void shadowed()
{
    //create ray from hit to light
    prd_shadow.attenuation = make_float3(0.0f);
    rtTerminateRay();
}


/*! * \fn shade
 * \brief shade method for ray color
 * \var shadowPrd Shadow ray data (attenuation)
 * \var hitPoint Intersection coords with object
 * \var shadowDriection 3d vector of the shadow direction
 * \var shadowRay New ray to trace the shadow
 *
 * generate color, trace new shadow ray
 */

static __device__ void shade()
{
    PerRayData_shadow shadowPrd;
    shadowPrd.attenuation = make_float3(1.0f);
    float4 result = make_float4(0.0f,0.0f,0.0f,1.0f);
    for(unsigned int i = 0;i < lights.size();++i)
    {
        float3 hitPoint = ray.origin + intersectionDistance * ray.direction;
        float3 shadowDirection = lights[i].position - hitPoint;
        float maxLambda = length(shadowDirection);
        shadowDirection = normalize(shadowDirection);
        hitPoint = hitPoint + sceneEpsilon * shadowDirection;

        Ray shadowRay = make_Ray(hitPoint, shadowDirection,
                                 shadowRayType, sceneEpsilon,maxLambda);

        //trace new shadow ray
        rtTrace(topShadower, shadowRay, shadowPrd);
        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            float4 ret = make_float4(color,1.f) * make_float4(lights[i].color,1.f);
            ret *= (lights[i].intensity * dot(normal,shadowDirection)) / (maxLambda * maxLambda);
            result += ret;
        }
    }
    result.w = 1.0f;
    prd_radiance.result = result/lights.size();
}

