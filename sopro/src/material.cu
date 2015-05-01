/*!
 * TODO: closest hit
 * anyhit, for shadows
 *
 */

#include "../include/material.h"

using namespace optix;

/*! \fn shadowed
 * \brief method to generate a shadow
 *
 * generate a new shadow ray if a the ray hits an object
 */

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
    //create ray from hit to light
    prd_shadow.attenuation = make_float3(0.0f);
    rtTerminateRay();
}


/*! * \fn shade
 * \brief shade method ray color
 * \var shadowPrd shadow ray data
 * \var hitPoint intersection coords with object
 * \var shadowDriection 3d vector of the shadow direction
 * \var shadowRay is a new ray to trace the shadow
 *
 * generate color, trace new shadow ray
 */
static __device__ void shade()
{
    PerRayData_shadow shadowPrd;
    shadowPrd.attenuation = make_float3(1.0f);

    float3 hitPoint = ray.origin + intersectionDistance * ray.direction;
    float3 shadowDirection = lights[0].pos - hitPoint;
    shadowDirection = normalize(shadowDirection);

    Ray shadowRay(hitPoint, shadowDirection,
                  shadowRayType, sceneEpsilon);

    //trace new shadow ray
    rtTrace(topShadower, shadowRay, shadowPrd);
    if(fmaxf(shadowPrd.attenuation) > 0.0f)
    {
        prd_radiance.result = make_float4(color,1.f);
    }
    else
    {
        prd_radiance.result = make_float4(0.0f,0.0f,0.0f,1.0f);
    }

}

