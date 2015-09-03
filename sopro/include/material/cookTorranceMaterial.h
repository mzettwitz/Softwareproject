#ifndef COOKTORRANCEMATERIAL_H
#define COOKTORRANCEMATERIAL_H

#include "baseMaterial.h"

using namespace optix;


class CookTorranceMaterial : public BaseMaterial
{
private:
    float3 mColor;
    float mDiffuseCoeff;
    float mFresnelFactor;
    float mRoughness;
    float mReflectance;


public:

    CookTorranceMaterial(float3 color, float diffuseCoeff, float fresnelFactor, float roughness, float reflectance) : mColor(color),mDiffuseCoeff(diffuseCoeff), mFresnelFactor(fresnelFactor), mRoughness(roughness), mReflectance(reflectance)
    {
        mMaterialType = COOKTORRANCE;
        setPTXPath("cookTorranceMaterial.cu");
    }

    Material createMaterial(Context context) const override;

    CookTorranceMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<CookTorranceMaterial> in = std::dynamic_pointer_cast<CookTorranceMaterial>(in1);
        mColor = in->color();
        mDiffuseCoeff = in->diffuseCoeff();
        mFresnelFactor = in->fresnelFactor();
        mRoughness = in->roughness();
        mReflectance = in->reflectance();
        mMaterialType = COOKTORRANCE;
        setPTXPath("cookTorranceMaterial.cu");
    }

    CookTorranceMaterial(const std::shared_ptr<BaseMaterial> in1,float3 &newColor) : mColor(newColor)
    {
        std::shared_ptr<CookTorranceMaterial> in = std::dynamic_pointer_cast<CookTorranceMaterial>(in1);
        mDiffuseCoeff = in->diffuseCoeff();
        mFresnelFactor = in->fresnelFactor();
        mRoughness = in->roughness();
        mReflectance = in->reflectance();
        mMaterialType = COOKTORRANCE;
        setPTXPath("cookTorranceMaterial.cu");
    }

    CookTorranceMaterial(const std::shared_ptr<BaseMaterial> in1, float value, short pos)
    {
        std::shared_ptr<CookTorranceMaterial> in = std::dynamic_pointer_cast<CookTorranceMaterial>(in1);
        switch(pos)
        {
        case 1:
            mColor = in->color();
            mDiffuseCoeff = value;
            mFresnelFactor = in->fresnelFactor();
            mRoughness = in->roughness();
            mReflectance = in->reflectance();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        case 2:
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = value;
            mRoughness = in->roughness();
            mReflectance = in->reflectance();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        case 3:
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = in->fresnelFactor();
            mRoughness = value;
            mReflectance = in->reflectance();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        case 4:
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = in->fresnelFactor();
            mRoughness = in->roughness();
            mReflectance = value;
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        default:
            mColor = in->color();
            mDiffuseCoeff = in->diffuseCoeff();
            mFresnelFactor = in->fresnelFactor();
            mRoughness = in->roughness();
            mReflectance = in->reflectance();
            mMaterialType = COOKTORRANCE;
            setPTXPath("cookTorranceMaterial.cu");
            break;
        }
    }

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
    float reflectance();
    void setReflectance(const float &reflectance);


};


#endif
