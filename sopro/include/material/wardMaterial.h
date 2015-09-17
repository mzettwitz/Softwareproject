#ifndef WARD_H
#define WARD_H

#include "baseMaterial.h"

using namespace optix;

class WardMaterial : public BaseMaterial
{
private:

    float3  mColor;
    float   mDiffuseCoeff;
    float   mSpecularCoeff;
    float   mAnisotropicFactorU;
    float   mAnisotropicFactorV;

public:
    // ------------------------CTor
    // ------------ Advanced CTor
    WardMaterial(float3 color, float diffuseCoeff, float specularCoeff, float u, float v) :
        mColor(color),mDiffuseCoeff(diffuseCoeff),mSpecularCoeff(specularCoeff), mAnisotropicFactorU(u), mAnisotropicFactorV(v)
    {
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }

    //------------- Copy CTors
    // pass through
    WardMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<WardMaterial> in = std::dynamic_pointer_cast<WardMaterial>(in1);
        mColor = in->color();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mAnisotropicFactorU = in->anisotropicFactorU();
        mAnisotropicFactorV = in->anisotropicFactorV();
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }

    //Copy CTor, change color
    WardMaterial(const std::shared_ptr<BaseMaterial> in1, const float3 &newColor) : mColor(newColor)
    {
        std::shared_ptr<WardMaterial> in = std::dynamic_pointer_cast<WardMaterial>(in1);
        mAnisotropicFactorU = in->anisotropicFactorU();
        mAnisotropicFactorV = in->anisotropicFactorV();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }

    //Copy CTor, change attrributes
    WardMaterial(const std::shared_ptr<BaseMaterial> in1, float value, short pos)
    {
        std::shared_ptr<WardMaterial> in = std::dynamic_pointer_cast<WardMaterial>(in1);
        switch(pos)
        {
        case 1 : // anisotropic U
            mColor = in->color();
            mAnisotropicFactorU = value;
            mAnisotropicFactorV = in->anisotropicFactorV();
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
            break;
        case 2 : // anisotropic V
            mColor = in->color();
            mAnisotropicFactorU = in->anisotropicFactorU();
            mAnisotropicFactorV = value;
            mDiffuseCoeff = in->diffuseCoeff();
            mSpecularCoeff = in->specularCoeff();
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
            break;
        case 3 : // diffuseCoeff
            mColor = in->color();
            mAnisotropicFactorU = in->anisotropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mSpecularCoeff = in->specularCoeff();
            value + mSpecularCoeff < 1.f ? mDiffuseCoeff = value: mDiffuseCoeff = in->diffuseCoeff();
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
            break;
        case 4: // specular coeff
            mColor = in->color();
            mAnisotropicFactorU = in->anisotropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mDiffuseCoeff = in->diffuseCoeff();
            mDiffuseCoeff + value < 1.f ? mSpecularCoeff = value: mSpecularCoeff = in->specularCoeff();
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
            break;
        default : // pass through
            mColor = in->color();
            mAnisotropicFactorU = in->anisotropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mDiffuseCoeff = in->diffuseCoeff();
            mMaterialType = WARD;
            setPTXPath("wardMaterial.cu");
            break;
        }
    }

    //-------------CTor for material conversion
    // Lambert, Glass
    /*!
     * \brief CTor to generate a \class WardMaterial object based on a given color.
     *
     * \note Useful for conversion from \class LambertMaterial, \class GlassMaterial.
     *
     * \param col RGB color information for mColor.
     */
    WardMaterial(const float3 &col) : mColor(col)
    {
        mDiffuseCoeff = 0.49f;
        mSpecularCoeff = 0.5f;
        mAnisotropicFactorU = 0.5f;
        mAnisotropicFactorV = 0.5f;
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }
    // (Blinn-)Phong, Cook-Torrance
    /*!
     * \brief CTor to generate a \class WardMaterial object based on given attributes.
     *
     * \note Useful for conversion from \class PhongMaterial, \class BlinnPhongMaterial or \class CookTorranceMaterial.
     *
     * \param col RGB color information for mColor.
     * \param diffuseC Float vaule for mDiffuseCoeff.
     */
    WardMaterial(const float3 &col, float diffuseC) : mColor(col)
    {
        mDiffuseCoeff = diffuseC;
        mSpecularCoeff = 1.f-diffuseC;
        mAnisotropicFactorU = 0.5f;
        mAnisotropicFactorV = 0.5f;
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }


    Material createMaterial(Context context) const override;

    //Getter & Setter
    const float3& color() const;
    float3& color();
    void setColor(const float3 &color);

    const float& diffuseCoeff() const;
    float& diffuseCoeff();
    void setDiffuseCoeff(const float& diffuseCoeff);

    const float& anisotropicFactorU() const;
    float& anisotropicFactorU();
    void setAnisotropicFactorU(const float &u);

    const float& anisotropicFactorV() const;
    float& anisotropicFactorV();
    void setAnistropicFactorV(const float &v);

    const float& specularCoeff() const;
    float& specularCoeff();
    void setSpecularCoeff(const float &specularCoeff);
};


#endif
