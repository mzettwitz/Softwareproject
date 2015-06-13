/*! \file phongMaterial.h
 * \brief A Phong material header file.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains Phong based attributes like color(ambient, diffuse, specular) and shininess for materials and shadowing.
 *
 * \var mAmbientColor RGB color for ambient coloring
 * \var mDiffuseColor RGB color for diffuse material color
 * \var mSpecularColor RGB color for specular material color
 * \var mShininess float value for reflection degree
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

#include "../include/baseMaterial.h"

using namespace optix;

class phongMaterial : protected baseMaterial
{
private:
    float3 mAmbientColor;
    float3 mDiffuseColor;
    float3 mSpecularColor;
    float mShininess;

public:
    phongMaterial(float3 a, float3 d, float3 s, float shine, std::string path) :
        mAmbientColor(a), mDiffuseColor(d), mSpecularColor(s), mShininess(shine)
    {
        setPTXPath(path);
    }

    Material createMaterial(Context context) const;

    // Getter & Setter
    float3 ambientColor() const;
    void setAmbientColor(const float3 &ambientColor);
    float3 diffuseColor() const;
    void setDiffuseColor(const float3 &diffuseColor);
    float3 specularColor() const;
    void setSpecularColor(const float3 &specularColor);
    float shininess() const;
    void setShininess(float shininess);
};
