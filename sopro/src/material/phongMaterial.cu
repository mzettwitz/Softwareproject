//TODO: everything

#include "../../include/structs.h"

#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>

using namespace optix;

rtDeclareVariable(PerRayData_radiance,prd_radiance,rtPayload,);
rtDeclareVariable(PerRayData_shadow,prd_shadow,rtPayload,);
rtDeclareVariable(Ray,ray,rtCurrentRay,);
rtDeclareVariable(unsigned int, shadowRayType,,);
rtDeclareVariable(unsigned int, radianceRayType,,);
rtDeclareVariable(float, sceneEpsilon,,);
rtDeclareVariable(rtObject, topShadower,,);
rtDeclareVariable(unsigned int,maxDepth,,);
rtBuffer<PointLight> lights;
rtDeclareVariable(float,intersectionDistance,rtIntersectionDistance,);
rtDeclareVariable(float3, color,,);
rtDeclareVariable(float, ambientCoefficient,,);
rtDeclareVariable(float, diffuseCoefficient,,);
rtDeclareVariable(float, specularCoefficient,,);
rtDeclareVariable(float, shininess,,);
rtDeclareVariable(float, specularity,,);
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

static __device__ void shadowed()
{
    prd_shadow.attenuation = make_float3(0.0f);
    rtTerminateRay();
}

static __device__ void shade()
{
    PerRayData_shadow shadowPrd;
    shadowPrd.attenuation = make_float3(1.0f);

    float4 result = make_float4(0.0f,0.0f,0.0f,1.0f);
    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;





    for(unsigned int i = 0;i < lights.size();++i)
    {

        float3 lightDirection = lights[i].position - hitPoint;
        float maxLambda = length(lightDirection);
        lightDirection = normalize(lightDirection);
        hitPoint = hitPoint + sceneEpsilon * lightDirection;
        Ray shadowRay = make_Ray(hitPoint,lightDirection,shadowRayType,sceneEpsilon,maxLambda);

        rtTrace(topShadower,shadowRay,shadowPrd);

        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            //phong = Ka + Kd + Ks
            //E = lights[i].intensity * dot(normal.lightDirection)/dist²
            //Ka = ambientColor
            //Kd = E * (diffuseColor + diffuseCoefficient)
            //Ks = E * (dot(R,ray.direction)^shininess + specularCoefficient)
            //something like that

        }
    }
    //WILL NOT WORK!!!!
    if(specularity > 0.0f && prd_radiance.depth < maxDepth)
    {
        prd_radiance.depth++;
        float maxLambda = 10000;
        Ray reflectedRay = make_Ray(hitPoint,reflect(ray.direction,normal),radianceRayType,sceneEpsilon,maxLambda);
        //count depth + 1,
        rtTrace(topShadower,reflectedRay,prd_radiance);
        result = (1-specularity) * result + prd_radiance.result * specularity;
    }
}
