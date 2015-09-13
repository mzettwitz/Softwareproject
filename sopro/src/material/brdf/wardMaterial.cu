#include "../../../include/structs.h"

#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixu_matrix_namespace.h>
#include <curand.h>
#include <curand_kernel.h>
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
    float3 N = faceforward(shadingWorldNormal,-ray.direction,geometricWorldNormal);

    float3 V = normalize(-ray.direction);

    float3 Ks = make_float3(0,0,0);
    float3 Kd = make_float3(0,0,0);

    float3 fr = make_float3(0,0,0);
    float3 irradiance = make_float3(0,0,0);

    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;

    for(unsigned int i = 0;i < lights.size();++i)
    {
        shadowPrd.attenuation = make_float3(1.0f);

        float3 L = lights[i].position - hitPoint;
        float maxLambda = length(L);
        L = normalize(L);



        float radiance = lights[i].intensity / (maxLambda * maxLambda);

        Ray shadowRay = make_Ray(hitPoint,L,shadowRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower,shadowRay,shadowPrd);

        //F fresnel term
        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            // approximation
            float3 H = (L + V);
            H = normalize(H);

            // first term
            float ks = specularCoeff;

            float alphaX = anisotropicFactorU;
            float alphaY = anisotropicFactorV;

            float VdotN = dot(V,N);
            float LdotN = dot(L,N);

            float ks1 = ks/(4.f * M_PIf * alphaX * alphaY * sqrtf(VdotN*LdotN));

            // second term
            float3 X = orthoVector(N);
            X = normalize(X);
            float3 Y = cross(N,X);
            Y = normalize(Y);

            float HdotX = dot(H,X);
            float HdotY = dot(H,Y);
            float HdotN = dot(H,N);

            float HdX_aX_2 = (HdotX/alphaX) * (HdotX/alphaX);
            float HdY_aY_2 = (HdotY/alphaY) * (HdotY/alphaY);

            float ks2 = (HdX_aX_2 + HdY_aY_2) / (1 + HdotN);
            ks2 = -2.f*ks2;

            // final
            fr = diffuseCoeff * color / M_PI + ks1 * powf(M_Ef, ks2);
        }

        irradiance += fr * fmaxf(dot(N,L),0) * radiance * lights[i].color;
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
