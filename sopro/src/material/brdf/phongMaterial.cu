//TODO: fix the shading to the brdf

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
rtDeclareVariable(unsigned int,maxDepth,,);
rtBuffer<PointLight> lights;
rtDeclareVariable(float,intersectionDistance,rtIntersectionDistance,);
rtDeclareVariable(float3, color,,);
rtDeclareVariable(float, ambientCoefficient,,);
rtDeclareVariable(float, diffuseCoefficient,,);
rtDeclareVariable(float, specularCoefficient,,);
rtDeclareVariable(float, shininess,,);
rtDeclareVariable(float, specularity,,);
rtDeclareVariable(float3, geometricNormal, attribute geometricNormal,);
rtDeclareVariable(float3, shadingNormal, attribute shadingNormal,);


static __device__ void shadowed();
static __device__ void shade();

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
 * If there is shadow: add black, if there is no shadow, compute the phong based color.
 * Therefore we sum up the ambient light, the diffuse color and the specular color and add it,
 * weighted by the number of lights in the scene, to the resulting color.\n
 * At the end we generate and trace a new reflected \class Ray to compute the mirrored objects in the scene.
 *
 * \var shadowPrd The ray information for the shadow ray.
 * \var result RGBA color for the resulting color in the hitpoint.
 * \var p RGB color to sum up the three parts of the \class PhongMaterial
 * \var hitPoint 3D float vector for the intersection between camera ray and object
 * \var lightDirection 3D float vector for the direction of the actual lightsource
 * \var maxLambda Float value describing the distance between actual lightsource and hitpoint
 * \var reflectedLightRay 3D vector for the direction of the light ray, reflected on the object surface
 * \var shadowRay A \class Ray to determine if the hitpoint is shadowed by the actual lightsource and any object in the scene
 * \var reflectedRay A \class Ray to trace the camera \class Ray that is reflected on the specular surface (mirror effect)
 * \var color4F RGBA version of the RGB diffuse color to give the reflection a color(lighted areas must be colored, since light is emitted)
 *
 */
static __device__ void shade()
{
    PerRayData_shadow shadowPrd;

    float3 geometricWorldNormal = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD,geometricNormal));
    float3 shadingWorldNormal = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD,shadingNormal));
    float3 N = faceforward(shadingWorldNormal,-ray.direction,geometricWorldNormal);

    //color information
    float3 fr = make_float3(0.0f,0.0f,0.0f);
    float3 Kd = make_float3(0.0f,0.0f,0.0f);
    float3 Ka = make_float3(0.0f,0.0f,0.0f);
    float3 Ks = make_float3(0.0f,0.0f,0.0f);
    float3 irradiance = make_float3(0.0f,0.0f,0.0f);

    //hitpoint information
    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;

    //iterate through lights
    for(unsigned int i = 0;i < lights.size();++i)
    {
        //must be set here, otherways, only 1! shadow will be interpreted the right way
        shadowPrd.attenuation = make_float3(1.0f);
        //light values
        float3 L = lights[i].position - hitPoint;
        float maxLambda = length(L);
        L = normalize(L);

        //incoming light
        float radiance = lights[i].intensity / (maxLambda*maxLambda);

        //reflected Ray
        float3 R = reflect(L, N);
        R = normalize(R);

        // hitpoint offset
        hitPoint = sceneEpsilon * N + hitPoint;
        // trace new shadow ray
        Ray shadowRay = make_Ray(hitPoint,L,shadowRayType,sceneEpsilon,maxLambda);
        rtTrace(topShadower,shadowRay,shadowPrd);

        // ambient outside to lighten shadowed parts
        Ka = color *  ambientCoefficient;
        fr = Ka;

        // if not in shadow
        if(fmaxf(shadowPrd.attenuation) > 0.0f)
        {
            // material color * coeff * (positive)surface angle * lightintensity at hitpoint
            Kd = color * (diffuseCoefficient / M_PIf);
            // lightcolor * coeff * normalized shininess * (positive)angle between eye and reflected light ray ^ shininess * lightintensity at hitpoint
            Ks = make_float3(specularCoefficient * ((shininess + 2.f)/(2.f*M_PIf)) *
                    pow(fmaxf(dot(ray.direction, R),0.f), shininess));

            fr += Kd + Ks;
        }

        irradiance += fr * fmaxf(dot(N,L),0) * radiance * lights[i].color;
    }

    float4 result = make_float4(irradiance,1);
    // recursive reflections
    if(specularity > 0.0f && prd_radiance.depth < maxDepth)
    {

        PerRayData_radiance prd_radiance_reflect;
        prd_radiance_reflect.depth = prd_radiance.depth+1;

        float maxLambda = 10000.0f;
        Ray reflectedRay = make_Ray(hitPoint,reflect(ray.direction,N),radianceRayType,sceneEpsilon,maxLambda);
        rtTrace(topObject, reflectedRay, prd_radiance_reflect);
        result = (1.0f-specularity) * result + prd_radiance_reflect.result * specularity;
    }



    prd_radiance.result = result;


}
