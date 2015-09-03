#ifndef BLINNPHONGMATERIAL_H
#define BLINNPHONGMATERIAL_H

#include "baseMaterial.h"

using namespace optix;

class BlinnPhongMaterial : public BaseMaterial
{
private:
    float3  mColor;
    float   mAmbientCoeff;
    float   mDiffuseCoeff;
    float   mSpecularCoeff;
    float   mShininess;
    float   mSpecularity;

public:

    BlinnPhongMaterial(float3 color, float ambientCoeff, float diffuseCoeff, float specularCoeff, float shininess, float specularity) :
        mColor(color),mAmbientCoeff(ambientCoeff),mDiffuseCoeff(diffuseCoeff),mSpecularCoeff(specularCoeff),mShininess(shininess),mSpecularity(specularity)
    {
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }

    Material createMaterial(Context context) const override;

    BlinnPhongMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<BlinnPhongMaterial> in = std::dynamic_pointer_cast<BlinnPhongMaterial(in1);
        mColor = in->color();
        mAmbientCoeff = in->ambientCoeff();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mShininess = in->shininess();
        mSpecularity = in->specularity();
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }

    BlinnPhongMaterial(const std::shared_ptr<BaseMaterial> in1,float3 &newColor) : mColor(newColor)
    {
        std::shared_ptr<BlinnPhongMaterial> in = std::dynamic_pointer_cast<BlinnPhongMaterial(in1);
        mAmbientCoeff = in->ambientCoeff();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mShininess = in->shininess();
        mSpecularity = in->specularity();
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }

    BlinnPhongMaterial(const std::shared_ptr<BaseMaterial> in1,float value, short pos)
    {
        std::shared_ptr<BlinnPhongMaterial> in = std::dynamic_pointer_cast<BlinnPhongMaterial(in1);
        switch(pos)
        {
        case 1: // ambient coeff
            mColor = in->color();
            mAmbientCoeff = value;
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mShininess = in->shininess();
            mSpecularity = in->specularity();
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        case 2: // diffsue coeff
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = value;
            mSpecularCoeff = in->specularCoeff();
            mShininess = in->shininess();
            mSpecularity = in->specularity();
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        case 3: // specular coeff
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = value;
            mShininess = in->shininess();
            mSpecularity = in->specularity();
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        case 4: // shininess
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mShininess = value;
            mSpecularity = in->specularity();
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        case 5: // specularity
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mShininess = in->shininess();
            mSpecularity = value;
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        default: // pass through
            mColor = in->color();
            mAmbientCoeff = in->ambientCoeff();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mShininess = in->shininess();
            mSpecularity = in->specularity();
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        }
    }

    const float3& color() const;
    float3& color();
    void setColor(const float3 &color);

    const float& ambientCoeff() const;
    float& ambientCoeff();
    void setAmbientCoeff(const float &ambientCoeff);

    const float& diffuseCoeff() const;
    float& diffuseCoeff();
    void setDiffuseCoeff(const float &diffuseCoeff);

    const float& specularCoeff() const;
    float& specularCoeff();
    void setSpecularCoeff(const float &specularCoeff);

    const float& shininess() const;
    float& shininess();
    void setShininess(const float &shininess);

    const float& specularity() const;
    float& specularity();
    void setSpecularity(const float &specularity);
};



#endif
