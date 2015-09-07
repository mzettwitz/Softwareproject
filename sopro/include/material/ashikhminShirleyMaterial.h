/*! \file ashikhminShirleyMaterial.h
 *  \brief a Ashikhmin-Shirley Material header file.
 *  \author Martin Zettwitz, Michael Größler, 2015
 *
 *
 */

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
    float   mRs;    //specularCoefficient
    float   mRd;    //diffuseCoefficient

public:

    // ------------------------CTor
    // ------------ Advanced CTor
    AshikhminShirleyMaterial(float3 color, float anisotropicFactorU, float anisotropicFactorV,float rs,float rd) : mColor(color),mAnisotropicFactorU(anisotropicFactorU), mAnisotropicFactorV(anisotropicFactorV), mRs(rs),mRd(rd)
    {
        mMaterialType = ASHIKHMINSHIRLEY;
        setPTXPath("ashikhminShirleyMaterial.cu");
    }


    //------------- Copy CTors
    // pass through
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

    //Copy CTor, change color
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

    //Copy CTor, change attributes
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
            mAnisotropicFactorU = in->anisotropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mRs = value;
            mRd = in->rd();
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        case 4: //Rd
            mColor = in->color();
            mAnisotropicFactorU = in->anisotropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mRs = in->rs();
            mRd = value;
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        default: //pass through
            mColor = in->color();
            mAnisotropicFactorU = in->anisotropicFactorU();
            mAnisotropicFactorV = in->anisotropicFactorV();
            mRs = in->rs();
            mRd = in->rd();
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        }
    }

    //-------------CTor for material conversion
    // Lambert
    /*!
     * \brief CTor to generate a \class AshikhminShirleyMaterial object based on a given color.
     *
     * \note Useful for conversion from \class LambertMaterial.
     *
     * \param col RGB color information for mColor.
     */
    AshikhminShirleyMaterial(const float3 &col) : mColor(col)
    {
        mAnisotropicFactorU = 1.f;
        mAnisotropicFactorV = 1.f;
        mRs = 0.5f;
        mRd = 0.5f;
        mMaterialType = ASHIKHMINSHIRLEY;
        setPTXPath("ashikhminShirleyMaterial.cu");
    }
    // Cook-Torrance
    /*!
     * \brief CTor to generate a \class WardMaterial object based on given attributes.
     *
     * \note Useful for conversion from \class CookTorranceMaterial.
     *
     * \param col RGB color information for \var mColor.
     * \param diffuseC Float vaule for \var mRd.
     */
    AshikhminShirleyMaterial(const float3 &col, float diffuseC) : mColor(col)
    {
        mAnisotropicFactorU = 1.f;
        mAnisotropicFactorV = 1.f;
        mRs = 0.5f;
        mRd = 0.5f;
        mMaterialType = ASHIKHMINSHIRLEY;
        setPTXPath("ashikhminShirleyMaterial.cu");
    }
    // Ward, Glass
    /*!
     * \brief CTor to generate a \class WardMaterial object based on given attributes.
     *
     * \note Useful for conversion from \class GlassMaterial or \class WardMaterial.
     *
     * \param col RGB color information for mColor.
     * \param param FLoat value for \var mRs or \var mRd.
     * \param mat Short value to pick to materialType
     */
    AshikhminShirleyMaterial(const float3 &col, float param, short mat) : mColor(col)
    {
        switch(mat)
        {
        case 1: // ward
            mAnisotropicFactorU = 1.f;
            mAnisotropicFactorV = 1.f;
            mRs = 0.5f;
            mRd = param;
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
            break;
        case 2: //glass
            mAnisotropicFactorU = 1.f;
            mAnisotropicFactorV = 1.f;
            mRs = param;
            mRd = 0.5f;
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
        default:
            mAnisotropicFactorU = 1.f;
            mAnisotropicFactorV = 1.f;
            mRs = 0.5f;
            mRd = 0.5f;
            mMaterialType = ASHIKHMINSHIRLEY;
            setPTXPath("ashikhminShirleyMaterial.cu");
        }
    }


// (Blinn-)Phong
/*!
 * \brief CTor to generate a \class WardMaterial object based on given attributes.
 *
 * \note Useful for conversion from \class BlinnPhongMaterial or \class PhongMaterial.
 *
 * \param col RGB color information for \var mColor.
 * \param diffuseC Float value for \var mRd.
 * \param specC Flaot value for \var mRs
 */
AshikhminShirleyMaterial(const float3 &col, float diffuseC, float specC) : mColor(col)
{
    mAnisotropicFactorU = 1.f;
    mAnisotropicFactorV = 1.f;
    mRs = specC;
    mRd = diffuseC;
    mMaterialType = ASHIKHMINSHIRLEY;
    setPTXPath("ashikhminShirleyMaterial.cu");
}


    Material createMaterial(Context context) const override;

    //Getter & Setter
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
