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
            /*
            // Monte-Carlo correct
            //------------------------------------computing ward, based on: http://www.graphics.cornell.edu/~bjw/wardnotes.pdf
            //------------------- alphaX and alphaY
            float alphaX = anisotropicFactorU;
            float alphaY = anisotropicFactorV;
            float alphaX_2 = alphaX*alphaX;
            float alphaY_2 = alphaY*alphaY;

            //------------------- random normal directions u,v using cuRAND http://docs.nvidia.com/cuda/curand/device-api-overview.html#distributions
            float u, v;
            curandState_t state;
            u = curand_uniform(&state);
            v = curand_uniform(&state);

            //----------------- computing angles for directions
            // phiH = arctan((alphaY/alphaX)*tan(2*Pi*v))
            float phiH = atanf((alphaY/alphaX)*tanf(2*M_PIf*v));
            float cos_PhiH = cosf(phiH);
            float cos_2_PhiH = cos_PhiH * cos_PhiH;
            float sin_PhiH = sinf(phiH);
            float sin_2_PhiH = sin_PhiH * sin_PhiH;

            // thetaH = arctan(sqrt((-logU)/(cos²phiH/alpaX²)+(sin²phiH)/alphaY²)
            float thetaH = atanf(sqrtf((-1.f*logf(u))/(cos_2_PhiH/alphaX_2)+(sin_2_PhiH/alphaY_2)));
            float cos_ThetaH = cosf(thetaH);
            float cos_2_ThetaH = cos_ThetaH * cos_ThetaH;
            float sin_ThetaH = sinf(thetaH);

            //------------------ half vector h
            // h = [sin thetaH * cos phiH, sin thetaH * sin phiH, cos thetaH]
            float3 h = make_float3(sin_ThetaH * cos_PhiH, sin_ThetaH * sin_PhiH, cos_ThetaH);
            h = normalize(h);

            float hdotV = dot(h,V);

            //------------------ outgoing O
            // O = 2( V(ingoing) dot h)*h - V
            float3 O = 2 * (hdotV)*h - V;
            O = normalize(O);

            //----------------- density function pO
            // s = -tan² thetaH * ((cos² phiH)/alphaX² + (sin² phiH)/alphaY²)
            float s = -1.f * powf(tanf(thetaH),2) * ((cos_2_PhiH / alphaX_2) + ((sin_2_PhiH / alphaY_2)));
            // (1/(4 * pi * alphaX * alphaY * (h dot V) * cos³ thetaH)) * e^s
            float pO = (1.f / ( 4 * M_PIf * alphaX * alphaY * hdotV * cos_2_ThetaH * cos_ThetaH)) * powf(M_Ef, s);

            //----------------- weighted function w
            float hdotN = dot(h,N);
            float OdotN = dot(O,N);
            //float OdotN = dot(L,N);
            float VdotN = dot(V,N);

            //w = specularCoeff*(h dot V)*(h dot N)³ * sqrt((O dot N)/(V dot N))
            float w = specularCoeff * hdotV * powf(hdotN,3) * sqrtf((OdotN)/(VdotN));

            fr = pO*w + diffuseCoeff * color / M_PI;    // ??????????
            */

            // approximated
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

            float ks2 = (HdX_aX_2 + HdY_aY_2) / (HdotN * HdotN);
            ks2 = -ks2;

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
