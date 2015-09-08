#include "../../../include/structs.h"

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
rtDeclareVariable(rtObject, topObject,,);
rtDeclareVariable(unsigned int, maxDepth,,);
rtBuffer<PointLight> lights;
rtDeclareVariable(float,intersectionDistance,rtIntersectionDistance,);
rtDeclareVariable(float3, color,,);
rtDeclareVariable(float, anisotropicFactorU,,);
rtDeclareVariable(float, anisotropicFactorV,,);
rtDeclareVariable(float, diffuseCoeff,,);
rtDeclareVariable(float, specularCoeff,,);
rtDeclareVariable(float3,geometricNormal,attribute geometricNormal,);
rtDeclareVariable(float3,shadingNormal,attribute shadingNormal,);

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

    float3 geometricWorldNormal = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD,geometricNormal));
    float3 shadingWorldNormal = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD,shadingNormal));
    float3 N = faceforward(shadingWorldNormal,-ray.direction,geometricWorldNormal);

    float3 V = normalize(-ray.direction);

    float3 Ks = make_float3(0,0,0);
    float3 Kd = make_float3(0,0,0);

    float3 fr =make_float3(0,0,0);
    float3 irradiance = make_float3(0,0,0);

    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;

    for(unsigned int i = 0;i < lights.size();++i)
    {
        fr = make_float3(0,0,0);
        shadowPrd.attenuation = make_float3(1.0f);

        float3 L = lights[i].position - hitPoint;
        float maxLambda = length(L);
        L = normalize(L);

        float3 H = (L + V) / length(L + V);
        H = normalize(H);

        float radiance = lights[i].intensity / (maxLambda * maxLambda);

        Ray shadowRay = make_Ray(hitPoint,L,shadowRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower,shadowRay,shadowPrd);

        //F fresnel term
        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            Kd = diffuseCoeff * color / M_PI;

            float NdotL = dot(N,L);
            float NdotV = dot(N,V);
            float NdotH = dot(N,H);
            float3 X = make_float3(1,0,0);         //NOT CORRECT
            float3 Y = make_float3(0,1,0);         //NOT CORRECT

            float HdotX = dot(H,X);
            float HdotY = dot(H,Y);

            float ks1 = 1/(sqrt(NdotL * NdotV));
            float ks2 = NdotL / (4 * M_PIf * anisotropicFactorU * anisotropicFactorV);
            float ks3 = HdotX / anisotropicFactorU;
            ks3 *= ks3;
            float ks4 = HdotY/ anisotropicFactorV;
            ks4 *= ks4;
            float ks5 = -2 * (ks3 + ks4)/(1 + NdotH);
            ks5 = exp(ks5);

            Ks = ks1 * ks2 * ks5 * color * specularCoeff;

            fr = Kd + Ks;
        }

        irradiance += fr * fmaxf(dot(N,L),0) * radiance * lights[i].color;
    }

    irradiance = irradiance/lights.size();

    float4 result = make_float4(irradiance,1);

    prd_radiance.result = result;
}
