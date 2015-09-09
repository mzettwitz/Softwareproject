#ifndef COOKTORRANCEMATERIAL_H
#define COOKTORRANCEMATERIAL_H

#include "baseMaterial.h"

using namespace optix;


class CookTorranceMaterial : public BaseMaterial
{
private:

    float3 mColor;
    float mDiffuseCoeff;
    float mSpecularCoeff;
    float mFresnelFactor;
    float mRoughness;
    float mReflectance;

public:

    // ------------------------CTor
    // ------------ Advanced CTor
    CookTorranceMaterial(float3 color, float diffuseCoeff, float specularCoeff, float fresnelFactor, float roughness, float reflectance) : mColor(color),mDiffuseCoeff(diffuseCoeff),mSpecularCoeff(specularCoeff), mFresnelFactor(fresnelFactor), mRoughness(roughness), mReflectance(reflectance)
    {
        mMaterialType = COOKTORRANCE;
        setPTXPath("cookTorranceMaterial.cu");
    }

    //------------- Copy CTors
    // pass through
    CookTorranceMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<CookTorranceMaterial> in = std::dynamic_pointer_cast<CookTorranceMaterial>(in1);
        mColor = in->color();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mFresnelFactor = in->fresnelFactor();
        mRoughness = in->roughness();
        mReflectance = in->reflectance();
        mMaterialType = COOKTORRANCE;
        setPTXPath("cookTorranceMaterial.cu");
    }

    //Copy CTor, change color
    CookTorranceMaterial(const std::shared_ptr<BaseMaterial> in1, const float3 &newColor) : mColor(newColor)
    {
        std::shared_ptr<CookTorranceMaterial> in = std::dynamic_pointer_cast<CookTorranceMaterial>(in1);
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mFresnelFactor = in->fresnelFactor();
        mRoughness = in->roughness();
        mReflectance = in->reflectance();
        mMaterialType = COOKTORRANCE;
        setPTXPath("cookTorranceMaterial.cu");
    }

    //Copy CTor, change attributes
    CookTorranceMaterial(const std::shared_ptr<BaseMaterial> in1, float value, short pos)
    {
        std::shared_ptr<CookTorranceMaterial> in = std::dynamic_pointer_cast<CookTorranceMaterial>(in1);
        switch(pos)
        {
        case 1: //diffuse Coefficient
            mColor = in->color();
            value + mSpecularCoeff <= 1 ? mDiffuseCoeff = value : mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = in->fresnelFactor();
            mRoughness = in->roughness();
            mReflectance = in->reflectance();
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        case 2: //fresnel factor
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = value;
            mRoughness = in->roughness();
            mReflectance = in->reflectance();
            mMaterialType = COOKTORRANCE;
            mSpecularCoeff = in->specularCoeff();
            setPTXPath("cookTorranceMaterial.cu");
            break;
        case 3: //roughness
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = in->fresnelFactor();
            mRoughness = value;
            mReflectance = in->reflectance();
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        case 4: //reflectance
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = in->fresnelFactor();
            mRoughness = in->roughness();
            mReflectance = value;
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        case 5: //specular coeff
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = in->fresnelFactor();
            mRoughness = in->roughness();
            mReflectance = in->reflectance();
            value + mDiffuseCoeff <= 1 ? mSpecularCoeff = value : mSpecularCoeff = in->specularCoeff();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        default:    //pass through
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = in->fresnelFactor();
            mRoughness = in->roughness();
            mReflectance = in->reflectance();
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        }
    }

    //-------------CTor for material conversion
    // Lambert, Glass
    /*!
     * \brief CTor to generate a \class CookTorranceMaterial object based on a given color.
     *
     * \note Useful for conversion from \class LambertMaterial or \class GlassMaterial.
     *
     * \param col RGB color information for mColor.
     */
    CookTorranceMaterial(const float3 &col) :
        mColor(col)
    {
        mDiffuseCoeff = 0.5f;
        mFresnelFactor = 0.5f;
        mRoughness = 0.5f;
        mReflectance = 0.5f;
        mMaterialType = COOKTORRANCE;
        mSpecularCoeff = 0.5f;
        setPTXPath("cookTorranceMaterial.cu");
    }
    // Ward, Ashikhmin-Shirley
    /*!
     * \brief CTor to generate a \class PhongMaterial object based on a given attributes.
     *
     * \note Useful for conversion from \class WardMaterial , \class AshkikhminShirleyMaterial .
     *
     * \param col RGBA color information for mColor.
     * \param diffuseC Float value for mDiffuseCoeff.
     */
    CookTorranceMaterial(const float3 &col, float diffuseC) : mColor(col)
    {
            mDiffuseCoeff = diffuseC;
            mFresnelFactor = 0.5f;
            mRoughness = 0.5f;
            mReflectance = 0.5f;
            mSpecularCoeff = 1-diffuseC;
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
    }
    // (Blinn)-Phong
    /*!
     * \brief CTor to generate a \class CookTorrance object based on a given attributes.
     *
     * \note Useful for conversion from \class BlinnPhongMaterial or \class PhongMaterial.
     *
     * \param col RGBA color information for \var mColor.
     * \param diffuseC Float value for \var mDiffuseCoeff
     * \param spec Float value for \param mReflectance
     */
    CookTorranceMaterial(const float3 &col, float diffuseC, float spec) : mColor(col)
    {
        mDiffuseCoeff = diffuseC;
        mFresnelFactor = 0.5f;
        mRoughness = 0.5f;
        mReflectance = spec;
        mSpecularCoeff = 1- diffuseC;
        mMaterialType = COOKTORRANCE;
        setPTXPath("cookTorranceMaterial.cu");
    }


    Material createMaterial(Context context) const override;


    //Getter & Setter
    const float3& color() const;
    float3& color();
    void setColor(const float3 &color);

    const float& diffuseCoeff() const;
    float& diffuseCoeff();
    void setDiffuseCoeff(const float &diffuseCoeff);

    const float& fresnelFactor() const;
    float& fresnelFactor();
    void setFresnelFactor(const float &fresnelFactor);

    const float& roughness() const;
    float& roughness();
    void setRoughness(const float &roughness);

    const float& reflectance() const;
    float& reflectance();
    void setReflectance(const float &reflectance);

    const float& specularCoeff() const;
    float& specularCoeff();
    void setSpecularCoeff(const float &specularCoeff);


};


#endif
