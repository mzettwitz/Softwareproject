#ifndef WARD_H
#define WARD_H

#include "baseMaterial.h"

using namespace optix;

class WardMaterial : public BaseMaterial
{
private:

    float3  mColor;
    float   mDiffuseCoeff;
    float   mX;
    float   mY;

public:

    WardMaterial(float3 color, float diffuseCoeff, float x, float y) : mColor(color),mDiffuseCoeff(diffuseCoeff), mX(x), mY(y)
    {
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }

    Material createMaterial(Context context) const override;

    WardMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<WardMaterial> in = std::dynamic_pointer_cast<WardMaterial>(in1);
        mColor = in->color();
        mDiffuseCoeff = in->diffuseCoeff();
        mX = in->x();
        mY = in->y();
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }

    //change color
    WardMaterial(const std::shared_ptr<BaseMaterial> in1, const float3 &newColor) : mColor(newColor)
    {
        std::shared_ptr<WardMaterial> in = std::dynamic_pointer_cast<WardMaterial>(in1);
        mX = in->x();
        mY = in->y();
        mDiffuseCoeff = in->diffuseCoeff();
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }

    //change coeffs

    WardMaterial(const std::shared_ptr<BaseMaterial> in1, float value, short pos)
    {
        std::shared_ptr<WardMaterial> in = std::dynamic_pointer_cast<WardMaterial>(in1);
        switch(pos)
        {
        case 1 : //x
            mColor = in->color();
            mX = value;
            mY = in->y();
            mDiffuseCoeff = in->diffuseCoeff();
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
            break;
        case 2 : // y
            mColor = in->color();
            mX = in->x();
            mY = value;
            mDiffuseCoeff = in->diffuseCoeff();
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
            break;
        case 3 : // diffuseCoeff
            mColor = in->color();
            mX = in->x();
            mY = in->y();
            mDiffuseCoeff = value;
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
        default : // pass through
            mColor = in->color();
            mX = in->x();
            mY = in->y();
            mDiffuseCoeff = in->diffuseCoeff();
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
            break;
        }
    }

    const float3& color() const;
    float3& color();
    void setColor(const float3 &color);

    const float& diffuseCoeff() const;
    float& diffuseCoeff();
    void setDiffuseCoeff(const float& diffuseCoeff);

    const float& x() const;
    float& x();
    void setX(const float &x);

    const float& y() const;
    float& y();
    void setY(const float &y);
};


#endif
