/*! \file phongMaterial.h
 * \brief A Phong material header file.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains Phong based attributes like color, coefficients, shininess and specularity for materials and shading.
 *
 * \var mMaterialType Value to define the material type (PHONG)
 * \var mColor RGB color for (diffuse) material color
 * \var mAmbientCoeff Flaot value between [0,1] to describe the ratio of ambient lighting
 * \var mDiffuseCoeff Flaot value between [0,1] to describe the ratio of diffuse light distribution
 * \var mSpecularCoeff Flaot value between [0,1] to describe the ratio of specular light distribution
 * \var mShininess Float value for specular light distribution power
 * \var mSpecularity Float value between [0,1] to describe the ability to reflect (mirroring)
 * \var prd_radiance Information about traced ray hit
 * \var prd_shadow Information about shadow attenuation
 * \var ray Incoming camera ray
 * \var shadowRayType Type ID of the shadow ray
 * \var radianceRayType Type ID of the traced ray
 * \var sceneEpsilon Safty distance to avoid self intersections
 * \var topShadower Top shadowing object in object tree
 * \var lights Lights of the Scene
 * \var intersectionDistance Distance from ray origin to intersection point
 */


#pragma once

#include "baseMaterial.h"

using namespace optix;

class PhongMaterial : public BaseMaterial
{
private:
    float3 mColor;
    float mAmbientCoeff;
    float mDiffuseCoeff;
    float mSpecularCoeff;
    float mShininess;
    float mSpecularity;

public:
    // ------------------------CTor
    // ------------advanced CTor
    /*!
     * \brief Advanced contructor to generate an instance of a PhongMaterial.
     *
     * \param col RGB float information about the (diffuse)color.
     * \param aCoef Float value to set the ambient coefficient.
     * \param dCoef Float value to set the diffuse coefficient.
     * \param sCoef Float value to set the specular coefficient.
     * \param shine Float value to set the shininess.
     * \param spec Float value to set the specularity.
     */
    PhongMaterial(float3 col, float aCoef, float dCoef, float sCoef, float shine, float spec) :
        mColor(col), mAmbientCoeff(aCoef), mDiffuseCoeff(dCoef), mSpecularCoeff(sCoef),
        mShininess(shine), mSpecularity(spec)
    {
        mMaterialType = PHONG;
        setPTXPath("phongMaterial.cu");
    }

    //------------- Copy CTors
    // pass through
    /*!
     * \brief Simple copy CTor to pass through an existing \class PhongMaterial object.
     *
     * \param in1 Smartpointer to the object you want to copy.
     */
    PhongMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<PhongMaterial> in = std::dynamic_pointer_cast<PhongMaterial>(in1);
        mColor = in->color();
        mAmbientCoeff = in->ambientCoeff();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mShininess = in->shininess();
        mSpecularity = in->specularity();
        mMaterialType = PHONG;
        setPTXPath("phongMaterial.cu");
    }
    // change color
    /*!
     * \brief Copy CTor to copy an existing \class PhongMaterial object and change it's color.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param newColor The new color you want to setup in your new object
     */
    PhongMaterial(const std::shared_ptr<BaseMaterial> in1, const float3 &newColor) :
        mColor(newColor)
    {
        std::shared_ptr<PhongMaterial> in = std::dynamic_pointer_cast<PhongMaterial>(in1);
        mAmbientCoeff = in->ambientCoeff();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mShininess = in->shininess();
        mSpecularity = in->specularity();
        mMaterialType = PHONG;
        setPTXPath("phongMaterial.cu");
    }
    // change coeffs
    /*!
     * \brief Advanced copy CTor to copy an existing \class PhongMaterial object and change an attribute.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param value The value for the attribute you want to change.
     * \param pos The specific attribute you want to change:
     * 1 = mAmbientCoeff
     * 2 = mDiffuseCoeff
     * 3 = mSpecularCoeff
     * 4 = mShininess
     * 5 = mSpecularity
     * any other = pass through
     */
    PhongMaterial(const std::shared_ptr<BaseMaterial> in1, float value, short pos)
    {
        std::shared_ptr<PhongMaterial> in = std::dynamic_pointer_cast<PhongMaterial>(in1);
        switch(pos)
        {
        case 1: // ambient coeff
            mColor = in->color();
            mAmbientCoeff = value;
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mShininess = in->shininess();
            mSpecularity = in->specularity();
            mMaterialType = PHONG;
            setPTXPath("phongMaterial.cu");
            break;
        case 2: // diffsue coeff
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = value;
            mSpecularCoeff = in->specularCoeff();
            mShininess = in->shininess();
            mSpecularity = in->specularity();
            mMaterialType = PHONG;
            setPTXPath("phongMaterial.cu");
            break;
        case 3: // specular coeff
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = value;
            mShininess = in->shininess();
            mSpecularity = in->specularity();
            mMaterialType = PHONG;
            setPTXPath("phongMaterial.cu");
            break;
        case 4: // shininess
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mShininess = value;
            mSpecularity = in->specularity();
            mMaterialType = PHONG;
            setPTXPath("phongMaterial.cu");
            break;
        case 5: // specularity
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mShininess = in->shininess();
            mSpecularity = value;
            mMaterialType = PHONG;
            setPTXPath("phongMaterial.cu");
            break;
        default: // pass through
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mShininess = in->shininess();
            mSpecularity = in->specularity();
            mMaterialType = PHONG;
            setPTXPath("phongMaterial.cu");
            break;
        }
    }

    //-------------CTor for material conversion
    // Lambert
    /*!
     * \brief CTor to generate a \class PhongMaterial object based on a given color.
     *
     * \note Useful for conversion from \class LambertMaterial.
     *
     * \param col RGB color information for mColor.
     */
    PhongMaterial(float3 col) :
        mColor(col)
    {
        mAmbientCoeff = 1.f;
        mDiffuseCoeff = 1.f;
        mSpecularCoeff = 1.f;
        mShininess = 1.f;
        mSpecularity = 1.f;
        mMaterialType = PHONG;
        setPTXPath("phongMaterial.cu");
    }

    Material createMaterial(Context context) const override;

    // ------------------------Getter & Setter
    const float3& color() const;
    float3& color();
    void setColor(const float3 &color);

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

    const float& specularity() const;
    float& specularity();
    void setSpecularity(float specularity);

};
