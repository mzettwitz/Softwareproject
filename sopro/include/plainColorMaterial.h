/*! \file plainColorMaterial.h
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

#include "baseMaterial.h"

using namespace optix;




class plainColorMaterial : protected baseMaterial
{

    float3 mColor;
public :
    plainColorMaterial(float3 c,std::string path) : mColor(c)
    {
        setPTXPath(path);
    }
    void setColor(const float3 &c);
    Material createMaterial(Context context) const;


};


