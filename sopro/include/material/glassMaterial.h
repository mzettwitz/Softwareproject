/*! \file glassMaterial.h
 * \brief A glass material header file.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains basic attributes like color and refractive index for materials and refractive shading.
 *
 * \var mColor RGBA color
 * \var mRefractiveIdx Float value of refractive index.
 * \var mSpecularity Float value to describe the ability to reflect light, range [0,1]
 * \var mShininess Float value for specular light distribution power (like Phong)
 * \var mSpecularCoeff Float value between [0,1] for ratio of light distribution
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


class GlassMaterial : public BaseMaterial
{
private:
    float4 mColor;
    float mRefractiveIdx;
    float mSpecularity;
    float mShininess;
    float mSpecularCoeff;

public :
    // -------------------- CTor
    //------------ Advanced CTor
    /*!
     * \brief CTor to generate a \class GlassMaterial object based on a given attributes.
     *
     * \param c RGB color information for \var mColor
     * \param idx Float value for \var mRefractiveIdx
     * \param spec Float value for \var mSpecularity
     * \param shine Float value for \var mShininess
     * \param specC Float value for \var mSpecularCoeff
     */
    GlassMaterial(float4 c, float idx, float spec, float shine, float specC) :
        mColor(c), mRefractiveIdx(idx), mSpecularity(spec), mShininess(shine), mSpecularCoeff(specC)
    {
        mMaterialType = GLASS;
        setPTXPath("glassMaterial.cu");
    }

    //----------- Copy CTors
    // pass through
    /*!
     * \brief Copy CTor to copy an existing \class GlassMaterial object.
     *
     * \param in1 Smartpointer to the object you want to copy.
     */
    GlassMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<GlassMaterial> in = std::dynamic_pointer_cast<GlassMaterial>(in1);
        mColor = in->color();
        mRefractiveIdx = in->refractiveIdx();
        mSpecularity = in->specularity();
        mShininess = in->shininess();
        mSpecularCoeff = in->specularCoeff();
        mMaterialType = GLASS;
        setPTXPath("glassMaterial.cu");
    }
    // change color
    /*!
     * \brief Copy CTor to copy an existing \class GlassMaterial object and change it's color.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param newColor The new color you want to change.
     */
    GlassMaterial(const std::shared_ptr<BaseMaterial> in1, const float4 &newColor) :
        mColor(newColor)
    {
        std::shared_ptr<GlassMaterial> in = std::dynamic_pointer_cast<GlassMaterial>(in1);
        mRefractiveIdx = in->refractiveIdx();
        mSpecularity = in->specularity();
        mShininess = in->shininess();
        mSpecularCoeff = in->specularCoeff();
        mMaterialType = GLASS;
        setPTXPath("glassMaterial.cu");
    }
    // change coeffs
    /*!
     * \brief Advanced Copy CTor to copy an existing \class GlassMaterial object and change an attribute.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param value The new value for the attribute you want to change.
     * \param pos The specific attribute you want to change:\n
     * 1 = refractive index\n
     * 2 = specularity\n
     * 3 = shininess\n
     * 4 = specular coefficient\n
     * any other = pass through
     */
    GlassMaterial(const std::shared_ptr<BaseMaterial> in1, float value, short pos)
    {
        std::shared_ptr<GlassMaterial> in = std::dynamic_pointer_cast<GlassMaterial>(in1);
        switch(pos)
        {
        case 1: //refractive index
            mColor = in->color();
            mRefractiveIdx = value;
            mSpecularity = in->specularity();
            mShininess = in->shininess();
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = GLASS;
            setPTXPath("glassMaterial.cu");
            break;
        case 2: // specularity
            mColor = in->color();
            mRefractiveIdx = in->refractiveIdx();
            mSpecularity = value;
            mShininess = in->shininess();
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = GLASS;
            setPTXPath("glassMaterial.cu");
            break;
        case 3: // shininess
            mColor = in->color();
            mRefractiveIdx = in->refractiveIdx();
            mSpecularity = in->specularity();
            mShininess = value;
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = GLASS;
            setPTXPath("glassMaterial.cu");
            break;
        case 4: // specular coefficient
            mColor = in->color();
            mRefractiveIdx = in->refractiveIdx();
            mSpecularity = in->specularity();
            mShininess = in->shininess();
            mSpecularCoeff = value;
            mMaterialType = GLASS;
            setPTXPath("glassMaterial.cu");
            break;
        default: //pass through
            mColor = in->color();
            mRefractiveIdx = in->refractiveIdx();
            mSpecularity = in->specularity();
            mShininess = in->shininess();
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = GLASS;
            setPTXPath("glassMaterial.cu");
            break;
        }
    }

    //-------------CTor for material conversion
    // Lambert
    /*!
     * \brief CTor to generate a \class GlassMaterial object based on a given color.
     *
     * \note Useful for conversion from \class LambertMaterial.
     *
     * \param col RGB color information for mColor.
     */
    GlassMaterial(const float3 &col)
    {
        mColor = make_float4(col.x, col.y, col.z, 0.5f);
        mRefractiveIdx = 1.0f;
        mSpecularity = 0.5f;
        mShininess = 1.0f;
        mSpecularCoeff = 1.0f;
        mMaterialType = GLASS;
        setPTXPath("glassMaterial.cu");
    }
    // Phong
    /*!
     * \brief CTor to generate a \class GlassMaterial object based on given attributes.
     *
     * \note Useful for conversion from \class PhongMaterial.
     *
     * \param col RGB color information for mColor.
     * \param spec Float vaule for mSpecularity.
     * \param shine Float value for mShininess.
     * \param specC Float value for mSpecularCoeff.
     */
    GlassMaterial(const float3 &col, float spec, float shine, float specC)
    {
        mColor = make_float4(col.x, col.y, col.z, 0.5f);
        mRefractiveIdx = 1.0f;
        mSpecularity = spec;
        mShininess = shine;
        mSpecularCoeff = specC;
        mMaterialType = GLASS;
        setPTXPath("glassMaterial.cu");
    }



    Material createMaterial(Context context) const override;

    // ------------------------Getter & Setter
    // Setter
    void setColor(const float4 &color);
    void setRefractiveIdx(const float idx);
    void setSpecularity(const float spec);
    void setShininess(const float shine);
    void setSpecularCoeff(const float specC);

    // Special getter for ATB
    const float4& color() const;
    float4& color();

    const float& refractiveIdx() const;
    float& refractiveIdx();

    const float& specularity() const;
    float& specularity();

    const float& shininess() const;
    float& shininess();

    const float& specularCoeff() const;
    float& specularCoeff();

};
