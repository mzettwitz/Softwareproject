/*! \file material.h
 * \brief A material header file.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains basic attributes like color for materials and shadowing.
 *
 * \var color RGB color
 * \var prd_radiance Information about traced ray hit
 * \var prd_shadow Information about shadow attenuation
 * \var ray Incoming camera ray
 * \var shadowRayType Type ID of the shadow ray
 * \var radianceRayType Type ID of the traced ray
 * \var sceneEpsilon Safty distance to avoid self intersections
 * \var topShadower Top Shadowing object in object tree
 * \var lights Lights of the Scene
 * \var intersectionDistance Distance from ray origin to intersection point
 */


#pragma once

#include <../cuda/commonStructs.h>
#include "../include/structs.h"
#include "optix.h"
#include "optixu/optixu_math_namespace.h"

using namespace optix;

rtDeclareVariable(float3,color,,);
rtDeclareVariable(PerRayData_radiance,prd_radiance,rtPayload,);
rtDeclareVariable(PerRayData_shadow,prd_shadow,rtPayload,);
rtDeclareVariable(optix::Ray, ray, rtCurrentRay,);
rtDeclareVariable(unsigned int, shadowRayType,,);
rtDeclareVariable(unsigned int, radianceRayType,,);
rtDeclareVariable(float, sceneEpsilon,,);
rtDeclareVariable(rtObject, topShadower,,);
rtBuffer<BasicLight> lights;
rtDeclareVariable(float, intersectionDistance, rtIntersectionDistance,);


RT_PROGRAM void anyhit_shadow();
RT_PROGRAM void closesthit_radiance();
static __device__ void shadowed();
static __device__ void shade();
