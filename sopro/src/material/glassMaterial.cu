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
static __device__ float3 refract(const float3 &ray_in, const float3 &normal, float n1, float n2);

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
    PerRayData_shadow shadowPrd;
    shadowPrd.attenuation = make_float3(1.0f);

    //color information
    float4 result = make_float4(0.0f,0.0f,0.0f,1.0f);
    float3 reflectiveColor = make_float3(0.0f,0.0f,0.0f);
    float3 refractiveColor = make_float3(0.0f,0.0f,0.0f);
    float3 glassColor = make_float3(0.0f,0.0f,0.0f);

    //hitpoint information
    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;

    //iterate through lights
    for(unsigned int i = 0;i < lights.size();++i)
    {
        //light values
        float3 lightDirection = lights[i].position - hitPoint;
        float maxLambda = length(lightDirection);
        float radiance = lights[i].intensity / (maxLambda*maxLambda);
        lightDirection = normalize(lightDirection);
        float3 reflectedLightRay = reflect(lightDirection, normal);
        reflectedLightRay = normalize(reflectedLightRay);

        // hitpoint offset
        hitPoint = hitPoint + sceneEpsilon * normal;

        // trace new shadow ray
        Ray shadowRay = make_Ray(hitPoint,lightDirection,shadowRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower,shadowRay,shadowPrd);

        result.x = color.x * color.w;
        result.y = color.y * color.w;
        result.z = color.z * color.w;

        // if not in shadow
        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            // add highlights with phong based light distribution

            // recursive refraction
            /* TODO:

            should look like:
            - compute the refracted direction
            - put actual material on a stack
            - trace new refracted ray till it hit's something different from glass material or nothing
                -> recursion
            */

            // phong based highlights
            glassColor += lights[i].color * specularCoeff * ((shininess + 2.f)/(2.f*M_PIf)) *
                    pow(fmaxf(dot(ray.direction, reflectedLightRay),0.f), shininess) * radiance;

        }
    }

    result.x += glassColor.x;
    result.y += glassColor.y;
    result.z += glassColor.z;

    // recursive reflections
    if(specularity > 0.0f && prd_radiance.depth < maxDepth)
    {
        prd_radiance.depth++;
        float maxLambda = 10000.0f;
        Ray reflectedRay = make_Ray(hitPoint,reflect(ray.direction,normal),radianceRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower, reflectedRay, prd_radiance);
        result = (1.0f-specularity) * result + prd_radiance.result * specularity;
    }

    // recursive refractions
    //TODO: IMPLEMENT STACK IN TRACE AND BEER'S LAW
    if(prd_radiance.depth < maxDepth)
    {
        prd_radiance.depth++;
        float maxLambda = 10000.0f;
        Ray refractedRay = make_Ray(hitPoint,refract(ray.direction,normal, 1.0f, refractiveIdx),radianceRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower, refractedRay, prd_radiance);
        result = (1.0f-specularity) * result + prd_radiance.result * specularity;
    }

    result.w = 1.0f;

    prd_radiance.result = result/lights.size();

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
static __device__ float3 refract(const float3 &ray_in, const float3 &normal, float n1, float n2)
{
    float alpha = dot(normal, ray_in);
    if(alpha > 1)
        return reflect(ray_in, normal);
    else
    {
        float n = n1/n2;
        float cosI = -1.0f * dot(normal, ray_in);
        float cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);
        //if(cosT2 > 0.0f)
        {
            float3 t = (n * ray_in + (n * cosI - sqrt(cosT2)) * normal);
            return t;
        }

    }
}
