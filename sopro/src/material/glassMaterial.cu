// TODO:
// - refraction method correct?
// - trace with stack
// - Beer's law

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
rtDeclareVariable(rtObject, topObject,,);
rtDeclareVariable(unsigned int,maxDepth,,);
rtBuffer<PointLight> lights;
rtDeclareVariable(float,intersectionDistance,rtIntersectionDistance,);
rtDeclareVariable(float4, color,,);
rtDeclareVariable(float, refractiveIdx,,);
rtDeclareVariable(float, specularity,,);
rtDeclareVariable(float, shininess,,);
rtDeclareVariable(float, specularCoeff,,);
rtDeclareVariable(float3, normal, attribute normal,);

static __device__ void shadowed();
static __device__ void shade();
static __device__ bool refract(const float3 &ray_in, const float3 &normal, float n1, float n2,float3 &T);

/*!
 * \brief Determines whether a shadow ray hits any object in the scene or not using \fn shadowed.
 */
RT_PROGRAM void anyhit_shadow()
{
    shadowed();
}

/*!
 * \brief Computes the closest intersection between camera ray and the \class SceneObject using \fn shade.
 */
RT_PROGRAM void closesthit_radiance()
{
    shade();
}

/*!
 * \brief Determines whether a shadow ray hits any object in the scene or not, sets the attenuation to 0 and terminates the ray.
 */
static __device__ void shadowed()
{
    prd_shadow.attenuation = make_float3(0.0f);
    rtTerminateRay();
}

/*!
 * \brief Computes the color of the closest intersection point from camera and object.
 *
 * Basicly we set up a resulting color. This color is basicly black, it gains more color information with each
 * computation for each light source in the scene. \n
 * First we compute the hitpoint on the object. Now we iterate through each lightsource in the scene
 * and generate a new \class Ray from lightsource to the object to trace the shadow (using anyhit).
 * If there is shadow: add black, if there is no shadow, compute the reflected and refracted color.
 * Therefore we reflect(generate) some rays to the outside and refract(generate) some rays to the inside. The refracted Ones depend on the
 * refractive index using Snell's law and Beer's law. \n
 *
 * \var shadowPrd The ray information for the shadow ray.
 * \var result RGBA color for the resulting color in the hitpoint.
 * \var reflectiveColor RGB color for reflective color information in the hitpoint
 * \var refractiveColor RGB color for the refractive color information in the hintpoint
 * \var glassColor RGB color for the sum of the reflection, refraction and the specular light distribution(phong based)
 * \var hitPoint 3D float vector for the intersection between camera ray and object
 * \var lightDirection 3D float vector for the direction of the actual lightsource
 * \var maxLambda Float value describing the distance between actual lightsource and hitpoint
 * \var reflectedLightRay 3D vector for the direction of the light ray, reflected on the object surface
 * \var refractedLightRay 3D vector for the direction of the light ray, refracted on the object surface
 * \var shadowRay A \class Ray to determine if the hitpoint is shadowed by the actual lightsource and any object in the scene
 * \var reflectedRay A \class Ray to trace the camera \class Ray that is reflected on the specular surface (mirror effect)
 * \var refractedRay A \class Ray to trace the camera \class Ray that is refracted on the transparent surface (refraction effect)
 *
 */
static __device__ void shade()
{

    //color information
    float4 result = make_float4(0.0f,0.0f,0.0f,1.0f);
    float3 reflectiveColor = make_float3(0.0f,0.0f,0.0f);
    float3 refractiveColor = make_float3(0.0f,0.0f,0.0f);
    float3 glassColor = make_float3(0.0f,0.0f,0.0f);

    //hitpoint information
    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;

    float3 D = ray.direction;
    float3 N = normal;
    float3 R = make_float3(0,0,0);
    float3 T = make_float3(0,0,0);
    float  dotD = 0;

    //outside of object
    if(dot(D,N))
    {
        R = reflect(D,N);
        refract(D,N,1,refractiveIdx,T);
        dotD = dot(-D,N);
    }
    //inside of object
    else
    {
        if(refract(D,-N,refractiveIdx,1,T))
        {
            dotD = dot(D,N);
        }
        else
        {
            R = reflect(D,-N);


            PerRayData_radiance prd_reflected;
            prd_reflected.depth = prd_radiance.depth+1;
            Ray reflectedRay = make_Ray(hitPoint,R,radianceRayType,sceneEpsilon,10000.0f);
            if(prd_reflected.depth < maxDepth)
            {
                rtTrace(topObject,reflectedRay,prd_reflected);
                result = prd_reflected.result;
            }
            prd_radiance.result = result;
            //rtTerminateRay();
        }
    }

    float r0 = ((1-refractiveIdx)*(1-refractiveIdx))/((1+refractiveIdx)*(1+refractiveIdx));
    float r1 = r0 + (1-r0) * (1-dotD) * (1-dotD) * (1-dotD) * (1-dotD) * (1-dotD);

    Ray reflectedRay = make_Ray(hitPoint,R,radianceRayType,sceneEpsilon,10000.0f);
    Ray refractedRay = make_Ray(hitPoint,T,radianceRayType,sceneEpsilon,10000.0f);

    PerRayData_radiance prd_reflected;
    prd_reflected.depth = prd_radiance.depth+1;
    PerRayData_radiance prd_refracted;
    prd_refracted.depth = prd_radiance.depth+1;

    if(prd_reflected.depth < maxDepth)
    {
        rtTrace(topObject,reflectedRay,prd_reflected);
    }
    if(prd_refracted.depth < maxDepth)
    {
<<<<<<< HEAD
        rtTrace(topObject,refractedRay,prd_refracted);
=======
        prd_radiance.depth++;
        float maxLambda = 10000.0f;
        Ray refractedRay = make_Ray(hitPoint,refract(ray.direction,normal, 1.0f, refractiveIdx),radianceRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower, refractedRay, prd_radiance);
        result = (color.w/255.0f) * result + prd_radiance.result * (1.0f - color.w/255.0f);
>>>>>>> 55e9146c63a8ffebffa5402065cc6401eff9db25
    }

    result = r1 * prd_reflected.result + (1-r1) * prd_refracted.result;

    result.w = 1.0f;

    prd_radiance.result = result;

}

/*!
 * \brief Refracts a ray (direction).
 *
 * Refracts a ray with two \class GlassMaterial objects, including total reflection, based on Snell's law
 *
 * \param ray_in The 3D ray direction that goes into the object
 * \param normal The 3D surface normal of the object that is entered
 * \param n1 The refractive index of the object, the ray is coming from
 * \param n2 The refractive index of the object, the ray is entering
 * \return The 3D ray direction that after getting refracted on the surface
 */
static __device__ bool refract(const float3 &D, const float3 &N, float n1, float n2,float3 &T)
{
    float d = (1 - (n1 * n1 * (1- dot(D,N) * dot(D,N)) / (n2 * n2)));
    if(d >= 0)
    {
        T = D - N * dot(D,N) * (n1/n2) - N * sqrt(d);
        return true;
    }


    return false;
}
