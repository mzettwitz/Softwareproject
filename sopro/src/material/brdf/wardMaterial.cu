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

    float ps = specularCoeff;

    float alphaX = anisotropicFactorU;
    float alphaY = anisotropicFactorV;

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
        hitPoint += n * sceneEpsilon;

        Ray shadowRay = make_Ray(hitPoint,L,shadowRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower,shadowRay,shadowPrd);

        // fr
        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            float3 h = (L + V);
            float3 x = orthoVector(n);
            x = normalize(x);
            float3 y = cross(n,x);
            y = normalize(y);


            // diffuse term kd
            float kd = diffuseCoeff / M_PIf;

            // specular term ks
            // refered to Moroder-Dür
            float ks = 0;

            float HdotX = dot(h,x);
            float HdotY = dot(h,y);

            float factor1 =  (1.f/(M_PIf*alphaX*alphaY));
            float factor2 = (-1.f/powf(dot(h, n),2));
            float factor3 = (HdotX/alphaX) * (HdotX/alphaX);
            float factor4 = (HdotY/alphaY) * (HdotY/alphaY);

            h = normalize(h);

            float factor5 = 1.f/(4*powf(dot(L,h),2)*powf(dot(h,n),4));

            float specRef = factor1 * expf(factor2 * (factor3+factor4))*factor5;

            if (specRef > 1e-10f)
                ks = ps * specRef;

            // final
            fr = color * kd + ks;
        }

        irradiance += (fr * fmaxf(dot(n,L),0) * radiance * lights[i].color) * shadowPrd.attenuation;
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
