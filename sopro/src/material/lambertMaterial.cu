
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


    float3 worldNormal = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD,normal));
    float3 N = faceforward(worldNormal,-ray.direction,worldNormal);
    //payload for shadow Ray
    PerRayData_shadow shadowPrd;
    //result color
    float4 result = make_float4(0.0f,0.0f,0.0f,1.0f);
    float3 fr = make_float3(0.0f,0.0f,0.0f);

    //iterate over every light source
    for(unsigned int i = 0;i < lights.size();++i)
    {

        shadowPrd.attenuation = make_float3(1.0f);

        //light values
        //get hitpoint on geometry
        float3 hitPoint = ray.origin + intersectionDistance * ray.direction;
        //get direction from hitpoint to lightsource
        float3 L = lights[i].position - hitPoint;
        float maxLambda = length(L);
        float radiance = lights[i].intensity / (maxLambda * maxLambda);
        L = normalize(L);

        //add sceneEpsilon
        hitPoint = hitPoint + sceneEpsilon * N;

        Ray shadowRay = make_Ray(hitPoint, L,
                                 shadowRayType, sceneEpsilon,maxLambda);

        //trace new shadow ray
        rtTrace(topShadower, shadowRay, shadowPrd);

        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            fr = color / M_PIf;
        }

        result += make_float4(fmaxf(dot(N,L),0) * fr * lights[i].color * radiance,1);

    }
    result.w = 1.0f;
    prd_radiance.result = result/lights.size();
}
