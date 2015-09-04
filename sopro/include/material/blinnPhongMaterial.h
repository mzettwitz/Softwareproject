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
    // ------------------------CTor
    // ------------ Advanced CTor
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
    BlinnPhongMaterial(float3 color, float ambientCoeff, float diffuseCoeff, float specularCoeff, float shininess, float specularity) :
        mColor(color),mAmbientCoeff(ambientCoeff),mDiffuseCoeff(diffuseCoeff),mSpecularCoeff(specularCoeff),mShininess(shininess),mSpecularity(specularity)
    {
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }

    //--------------Copy CTors
    // pass through
    BlinnPhongMaterial(const std::shared_ptr<BaseMaterial> in1)
    {
        std::shared_ptr<BlinnPhongMaterial> in = std::dynamic_pointer_cast<BlinnPhongMaterial>(in1);
        mColor = in->color();
        mAmbientCoeff = in->ambientCoeff();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mShininess = in->shininess();
        mSpecularity = in->specularity();
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }


    //Copy CTor, change color
    BlinnPhongMaterial(const std::shared_ptr<BaseMaterial> in1,const float3 &newColor) : mColor(newColor)
    {
        std::shared_ptr<BlinnPhongMaterial> in = std::dynamic_pointer_cast<BlinnPhongMaterial>(in1);
        mAmbientCoeff = in->ambientCoeff();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mShininess = in->shininess();
        mSpecularity = in->specularity();
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }

    //Copy CTor, change attributes
    BlinnPhongMaterial(const std::shared_ptr<BaseMaterial> in1,float value, short pos)
    {
        std::shared_ptr<BlinnPhongMaterial> in = std::dynamic_pointer_cast<BlinnPhongMaterial>(in1);
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

    //-------------CTor for material conversion
    // Lambert
    /*!
     * \brief CTor to generate a \class BlinnPhongMaterial object based on a given color.
     *
     * \note Useful for conversion from \class LambertMaterial.
     *
     * \param col RGB color information for mColor.
     */
    BlinnPhongMaterial(const float3 &col) :
        mColor(col)
    {
        mAmbientCoeff = 0.f;
        mDiffuseCoeff = 1.f;
        mSpecularCoeff = 1.f;
        mShininess = 1.f;
        mSpecularity = 0.5f;
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }
    // Glass, Cook-Torrance, Ashikhmin-Shirley
    /*!
     * \brief CTor to generate a \class BlinnPhongMaterial object based on a given attributes.
     *
     * \note Useful for conversion from \class GlassMaterial \class CookTorranceMaterial , \class AshkikhminShirleyMaterial .
     *
     * \param col RGBA color information for mColor.
     * \param mat Switch between different materials:
     * 1 = glass
     * 2 = Cook-Torrance
     * 3 = Ashikhmin-Shirley
     */
    BlinnPhongMaterial(const float3 &col, float param1, float param2, short mat)
    {
        switch(mat)
        {
        case 1: // glass
            mColor = col;
            mAmbientCoeff = 0.f;
            mDiffuseCoeff = 1.f;
            mSpecularCoeff = param1;
            mShininess = param2;
            mSpecularity = 0.5f;
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        case 2: // Cookr-Torrance
            mColor = col;
            mAmbientCoeff = 0.f;
            mDiffuseCoeff = param1;
            mSpecularCoeff = 0.5f;
            mShininess = 1.f;
            mSpecularity = param2;
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        case 3: // Ashikhmin-Shirley
            mColor = col;
            mAmbientCoeff = 0.f;
            mDiffuseCoeff = param1;
            mSpecularCoeff = param2;
            mShininess = 1.f;
            mSpecularity = 0.5f;
            mMaterialType = BLINNPHONG;
            setPTXPath("blinnPhongMaterial.cu");
            break;
        }
    }
    // Blinn-Phong
    /*!
     * \brief CTor to generate a \class BlinnPhongMaterial object based on a given attributes.
     *
     * \note Useful for conversion from \class BlinnPhongMaterial.
     *
     * \param in BlinnPhong object to copy.
     */
    BlinnPhongMaterial(const std::shared_ptr<BlinnPhongMaterial> in)
    {
        mColor = in->color();
        mAmbientCoeff = in->ambientCoeff();
        mDiffuseCoeff = in->diffuseCoeff();
        mSpecularCoeff = in->specularCoeff();
        mShininess = in->shininess();
        mSpecularity = in->specularity();
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }
    // Ward
    /*!
     * \brief CTor to generate a \class BlinnPhongMaterial object based on a given attributes.
     *
     * \note Useful for conversion from \class WardMaterial.
     *
     * \param col RGBA color information for \var mColor.
     * \param diffuseC Float value for \var mDiffuseCoeff
     */
    BlinnPhongMaterial(const float3 &col, float diffuseC)
    {
        mColor = col;
        mAmbientCoeff = 0.f;
        mDiffuseCoeff = diffuseC;
        mSpecularCoeff = 0.5f;
        mShininess = 1.f;
        mSpecularity = 0.5f;
        mMaterialType = BLINNPHONG;
        setPTXPath("blinnPhongMaterial.cu");
    }


    Material createMaterial(Context context) const override;


    //Getter & Setter
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
