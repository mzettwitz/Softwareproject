/*! \file material.h
 * \brief A material header file.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains basic attributes as color for materials and shadowing.
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
rtDeclareVariable(unsigned int, shadowType,,);
rtDeclareVariable(float, sceneEpsilon,,);
rtDeclareVariable(rtObject, topShadower,,);
rtBuffer<BasicLight> lights;
rtDeclareVariable(float, intersectionDistance, rtIntersectionDistance,);
