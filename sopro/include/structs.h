/*! \file structs.h
 * \brief A helpful file for our own used structs.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains simple structs that are used in the whole project
 */


#pragma once

#include <../cuda/commonStructs.h>

using namespace optix;

/*! * \struct PerRayData_shadow
 *
 * \brief ShadowRays
 *
 * Contains Optix information about attenuation/occlusion of a shadow ray.
 */

struct PerRayData_shadow
{
    float3 attenuation;     //12
    int padding;            //16 :)
};

/*! * \struct PerRayData_radiance
 *
 * \brief Color of basic ray
 *
 * Contains information about the returned color of a basic ray.
 */

struct PerRayData_radiance
{
    float4 result;          //16
    float importance;       //20
    int depth;              //24
    float2 padding;         //32 :)
};

struct PointLight
{

    float3 position;        //12
    float3 color;           //24
    float intensity;        //28
    int padding;            //32 :)
};
