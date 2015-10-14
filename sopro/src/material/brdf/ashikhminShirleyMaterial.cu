#include "../../../include/structs.h"

#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <math.h>

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

static __device__ float3 orthoVector(float3 in);

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
    float3 n = faceforward(shadingWorldNormal,-ray.direction,geometricWorldNormal);
    n = normalize(n);

    float3 V = normalize(-ray.direction);

    float3 fr = make_float3(0,0,0);
    float3 irradiance = make_float3(0,0,0);

    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;

    float rd = diffuseCoeff;
    float rs = specularCoeff;

    float nU = anisotropicFactorU;
    float nV = anisotropicFactorV;

    // iterate over lights
    for(unsigned int i = 0;i < lights.size();++i)
    {
        shadowPrd.attenuation = make_float3(1.0f);

        // light values
        float3 L = lights[i].position - hitPoint;
        float maxLambda = length(L);
        L = normalize(L);

        float radiance = lights[i].intensity / (maxLambda * maxLambda);

        // offset
        hitPoint += (n * sceneEpsilon);

        Ray shadowRay = make_Ray(hitPoint,L,shadowRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower,shadowRay,shadowPrd);

        // fr
        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            float3 h = (L + V);
            h = normalize(h);

            float VdotN = dot(V,n);
            float LdotN = dot(L,n);
            float LdotH = dot(L,h);

            // diffuse term pd
            float pd = ((28.f*rd)/(23.f*M_PIf))*(1.f-rs) * (1.f-powf(1.f-LdotN/2.f,5.f)) * (1.f-powf(1.f-VdotN/2.f,5.f));

            // Fresnel term F by Schlick's approximation
            float F = rs + (1.f - rs)*(powf(1.f-LdotH,5.f));

            // base vectors
            float3 u = orthoVector(n);
            u = normalize(u);
            float3 v = cross(n,u);
            v = normalize(v);

            float HdotU = dot(h,u);
            float HdotV = dot(h,v);
            float HdotN = dot(h,n);

            // specular term ps
            float ps1 = sqrtf((nU + 1.f) * (nV + 1.f)) / (8.f * M_PIf);
            float ps2 = powf(HdotN, (nU * HdotU * HdotU + nV * HdotV * HdotV)/(1.f - HdotN * HdotN));
            float ps3 = LdotH * fmaxf(LdotN, VdotN);

            float ps = ps1 * (ps2/ps3) * F;

            // final
            fr = color * pd + ps;
        }

        irradiance += fr * fmaxf(dot(n,L),0) * radiance * lights[i].color;
    }

    float4 result = make_float4(irradiance,1);

    prd_radiance.result = result;
}

// compute a vector, perpendicular to the input vector
static __device__ float3 orthoVector(float3 in)
{
    float3 out = make_float3(0,0,0);

    if(in.y == 0.f)         // y = 0
    {
        out.x = 1.f;
        if(in.z == 0.f)     // y = 0, z = 0
            return out;
        else
        {
            out.z = (in.x * out.x) / -in.z;
            return out;
        }
    }
    else if(in.z == 0.f)    // z = 0
    {
        out.x = 1.f;
        out.y = (in.x * out.x) / -in.y;
        return out;
    }
    else
    {
        out.y = 1.f;
        if(in.x == 0.f && in.z == 0.f)  // x = 0, z = 0
            return out;
        else
        {
            out.z = (in.y * out.y) / -in.z;
            return out;
        }
    }
}
