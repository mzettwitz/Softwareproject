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
    // ------------------------CTor
    // ------------ Advanced CTor
    WardMaterial(float3 color, float diffuseCoeff, float x, float y) : mColor(color),mDiffuseCoeff(diffuseCoeff), mX(x), mY(y)
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
        mX = in->x();
        mY = in->y();
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }

    //Copy CTor, change color
    WardMaterial(const std::shared_ptr<BaseMaterial> in1, const float3 &newColor) : mColor(newColor)
    {
        std::shared_ptr<WardMaterial> in = std::dynamic_pointer_cast<WardMaterial>(in1);
        mX = in->x();
        mY = in->y();
        mDiffuseCoeff = in->diffuseCoeff();
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }

    //Copy CTor, change attrributes
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
        mDiffuseCoeff = 1.0f;
        mX = 0.5f;
        mY = 0.5f;
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
        mX = 0.5f;
        mY = 0.5f;
        mMaterialType = WARD;
        setPTXPath("wardMaterial.cu");
    }
    // Ashikhmin-Shirley
    /*!
     * \brief CTor to generate a \class WardMaterial object based on given attributes.
     *
     * \note Useful for conversion from \class AshikhminShirleyMaterial.
     *
     * \param col RGB color information for mColor.
     * \param diffuseC FLoat value for mDiffuseCoeff.
     * \param u Float value for mX;
     * \param v Float value for mY;
     */
    WardMaterial(const float3 &col, float diffuseC, float u, float v) : mColor(col)
    {
        mDiffuseCoeff = diffuseC;
        mX = u / fmaxf(u,v);
        mY = v / fmaxf(u,v);
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

    const float& x() const;
    float& x();
    void setX(const float &x);

    const float& y() const;
    float& y();
    void setY(const float &y);
};


#endif
