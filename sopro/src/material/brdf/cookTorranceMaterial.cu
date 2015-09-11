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
rtDeclareVariable(float,diffuseCoefficient,,);
rtDeclareVariable(float,specularCoefficient,,);
rtDeclareVariable(float,fresnelFactor,,);
rtDeclareVariable(float,roughness,,);
rtDeclareVariable(float,reflectance,,);
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

    float3 fr = make_float3(0,0,0);
    float3 irradiance = make_float3(0,0,0);
    //for specular term
    //Ks = color * (D *F *G) / (4 * VdotN * NdotL)
    float D = 0;
    float F = 0;
    float G = 0;

    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;

    for(unsigned int i = 0;i < lights.size();++i)
    {
        fr = make_float3(0,0,0);

        shadowPrd.attenuation = make_float3(1.0f);

        float3 L = lights[i].position - hitPoint;

        float maxLambda = length(L);
        L = normalize(L);

        float3 H = (L + V) / length(L+V);
        H = normalize(H);
        float radiance = lights[i].intensity / (maxLambda * maxLambda);

        Ray shadowRay = make_Ray(hitPoint,L,shadowRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower,shadowRay,shadowPrd);

        //F fresnel term
        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
        F = pow((1 + dot(V,N)),fresnelFactor);

        //G geometric attenuation

        float HdotN = dot(H,N);
        float VdotN = dot(V,N);
        float VdotH = dot(V,H);
        float LdotN = dot(L,N);

        float g1 = (2 * HdotN * VdotN)/VdotH;
        float g2 = (2 * HdotN * LdotN)/VdotH;

        G = fminf(1,fminf(g1,g2));

        //D Beckmann distribution

        float alpha = acos(HdotN);
        float cosSqalpha = cos(alpha) * cos(alpha);

        float d1 = (1-cosSqalpha)/(cosSqalpha* roughness * roughness);


        D = exp(-d1)/(M_PIf * roughness * roughness * cosSqalpha*cosSqalpha);

        Ks = (D * F * G)/(4 * VdotN * LdotN) * color * specularCoefficient;

        Kd = color * diffuseCoefficient / M_PI;

        fr += Kd + Ks;
        }

        irradiance += fr * fmaxf(dot(N,L),0) * radiance * lights[i].color;

    }

    float4 result = make_float4(irradiance,1);

    // recursive reflections
    if(reflectance > 0.0f && prd_radiance.depth < maxDepth)
    {

        PerRayData_radiance prd_radiance_reflect;
        prd_radiance_reflect.depth = prd_radiance.depth+1;

        float maxLambda = 10000.0f;
        Ray reflectedRay = make_Ray(hitPoint,reflect(ray.direction,N),radianceRayType,sceneEpsilon,maxLambda);
        rtTrace(topObject, reflectedRay, prd_radiance_reflect);
        result = (1.0f-reflectance) * result + prd_radiance_reflect.result * reflectance;
    }

    prd_radiance.result = result;
}
