#ifndef ASHIKHMINSHIRLEYMATERIAL_H
#define ASHIKHMINSHIRLEYMATERIAL_H

#include "baseMaterial.h"

using namespace optix;

class AshikhminShirleyMaterial : public BaseMaterial
{
private:

    float3  mColor;
    float   mAnisotropicFactorU;
    float   mAnisotropicFactorV;
    float   mRs;
    float   mRd;

public:

    AshikhminShirleyMaterial(float3 color, float anisotropicFactorU, float anisotropicFactorV,float rs,float rd) : mColor(color),mAnisotropicFactorU(anisotropicFactorU), mAnisotropicFactorV(anisotropicFactorV), mRs(rs),mRd(rd)
    {
        mMaterialType = ASHIKHMINSHIRLEY;
        setPTXPath("ashikhminShirleyMaterial.cu");
    }

    Material createMaterial(Context context) const override;

    AshikhminShirleyMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<AshikhminShirleyMaterial> in = std::dynamic_pointer_cast<AshikhminShirleyMaterial>(in1);
        mColor = in->color();
        mAnisotropicFactorU =in->anisotropicFactorU();
        mAnisotropicFactorV = in->anisotropicFactorV();
        mRs = in->rs();
        mRd = in->rd();
        mMaterialType = ASHIKHMINSHIRLEY;
        setPTXPath("ashikhminShirleyMaterial.cu");
    }

    //change color
    AshikhminShirleyMaterial(const std::shared_ptr<BaseMaterial> in1, const float3 &newColor) :mColor(newColor)
    {
        std::shared_ptr<AshikhminShirleyMaterial> in = std::dynamic_pointer_cast<AshikhminShirleyMaterial>(in1);
        mAnisotropicFactorU =in->anisotropicFactorU();
        mAnisotropicFactorV = in->anisotropicFactorV();
        mRs = in->rs();
        mRd = in->rd();
        mMaterialType = ASHIKHMINSHIRLEY;
        setPTXPath("ashikhminShirleyMaterial.cu");
    }

    //change coeffs

    AshikhminShirleyMaterial(const std::shared_ptr<BaseMaterial> in1, float value, short pos)
    {
        std::shared_ptr<AshikhminShirleyMaterial> in = std::dynamic_pointer_cast<AshikhminShirleyMaterial>(in1);
        switch(pos)
        {
        case 1: //anistropic U
            mColor = in->color();
            mAnisotropicFactorU = value;
            mAnisotropicFactorV = in->anisotropicFactorV();
            mRs = in->rs();
            mRd = in->rd();
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        case 2: //anistropic V
            mColor = in->color();
            mAnisotropicFactorU = in->anisotropicFactorU();
            mAnisotropicFactorV = value;
            mRs = in->rs();
            mRd = in->rd();
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        case 3: //Rs
            mColor = in->color();
            mAnisotropicFactorU = in->anistropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mRs = value;
            mRd = in->rd();
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        case 4: //Rd
            mColor = in->color();
            mAnisotropicFactorU = in->anistropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mRs = in->rs();
            mRd = value;
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        default: //pass through
            mColor = in->color();
            mAnisotropicFactorU = in->anistropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mRs = in->rs();
            mRd = in->rd();
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        }

    }

    const float3& color() const;
    float3& color();
    void setColor(const float3 &color);

    const float& anisotropicFactorU() const;
    float& anisotropicFactorU();
    void setAnistropicFactorU(const float &u);

    const float& anisotropicFactorV() const;
    float& anisotropicFactorV();
    void setAnistropicFactorV(const float &v);

    const float& rs() const;
    float& rs();
    void setRs(const float &rs);

    const float& rd() const;
    float& rd();
    void setRd(const float &rd);
};

#endif
