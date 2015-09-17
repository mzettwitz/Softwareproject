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
rtDeclareVariable(float, diffuseCoeff,,);
rtDeclareVariable(float, specularCoeff,,);
rtDeclareVariable(float, metallic,,);
rtDeclareVariable(float,subsurface,,);
rtDeclareVariable(float,specular,,);
rtDeclareVariable(float,specualarTint,,);
rtDeclareVariable(float,roughness,,);
rtDeclareVariable(float, anisotropic,,);
rtDeclareVariable(float, sheen,,);
rtDeclareVariable(float, sheenTint,,);
rtDeclareVariable(float, clearcoat,,);
rtDeclareVariable(float, clearcoatGloss,,);
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
 * \var L 3D float vector for the direction of the actual lightsource
 * \var maxLambda Float value describing the distance between actual lightsource and hitpoint
 * \var R 3D vector for the direction of the light ray, reflected on the object surface
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


    prd_radiance.result = make_float4(0.0f);
}

