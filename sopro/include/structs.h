/*! \file structs.h
 * \brief A helpful file for our own used structs.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains simple structs that are used in the whole project
 */

/*! * \struct PerRayData_shadow
 *
 * \brief ShadowRays
 *
 * Contains Optix information about attenuation/occlusion of a shadow ray.
 */

/*! * \struct PerRayData_radiance
 *
 * \brief Color of basic ray
 *
 * Contains information about the returned color of a basic ray.
 */

#pragma once

#include <../cuda/commonStructs.h>

struct PerRayData_shadow
{
    float3 attenuation;     //12
    int padding;            //16 :)
};

struct PerRayData_radiance
{
    float4 result;          //16
    float importance;       //20
    int depth;              //24
    float2 padding;         //32 :)
};
