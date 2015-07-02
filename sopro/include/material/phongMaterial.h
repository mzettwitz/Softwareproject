/*! \file phongMaterial.h
 * \brief A Phong material header file.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains Phong based attributes like color(ambient, diffuse, specular) and shininess for materials and shadowing.
 *
 * \var mAmbientColor RGB color for ambient coloring
 * \var mDiffuseColor RGB color for diffuse material color
 * \var mSpecularColor RGB color for specular material color
 * \var mAmbientCoeff flaot value between [0,1] to describe the ratio of ambient color
 * \var mDiffuseCoeff flaot value between [0,1] to describe the ratio of diffuse color
 * \var mSpecularCoeff flaot value between [0,1] to describe the ratio of specular color
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

#include "baseMaterial.h"

using namespace optix;

class PhongMaterial : public BaseMaterial
{
private:
    float3 mAmbientColor;
    float3 mDiffuseColor;
    float3 mSpecularColor;
    float mAmbientCoeff;
    float mDiffuseCoeff;
    float mSpecularCoeff;
    float mShininess;

public:
    PhongMaterial(float3 aCol, float3 dCol, float3 sCol, float aCoef, float dCoef, float sCoef, float shine) :
        mAmbientColor(aCol), mDiffuseColor(dCol), mSpecularColor(sCol), mAmbientCoeff(aCoef), mDiffuseCoeff(dCoef), mSpecularCoeff(sCoef), mShininess(shine)
    {
        mMaterialType = PHONG;
        setPTXPath("phongMaterial.cu");
    }

    Material createMaterial(Context context) const override;

    // Getter & Setter
    const float3& ambientColor() const;
    float3& ambientColor();
    void setAmbientColor(const float3 &ambientColor);

    const float3& diffuseColor() const;
    float3& diffuseColor();
    void setDiffuseColor(const float3 &diffuseColor);

    const float3& specularColor() const;
    float3& specularColor();
    void setSpecularColor(const float3 &specularColor);

    const float& ambientCoeff() const;
    float& ambientCoeff();
    void setAmbientCoeff(float ambientCoeff);

    const float& diffuseCoeff() const;
    float& diffuseCoeff();
    void setDiffuseCoeff(float diffuseCoeff);

    const float& specularCoeff() const;
    float& specularCoeff();
    void setSpecularCoeff(float specularCoeff);

    const float& shininess() const;
    float& shininess();
    void setShininess(float shininess);

};
