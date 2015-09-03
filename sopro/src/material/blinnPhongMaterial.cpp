#include "../../include/material/blinnPhongMaterial.h"

using namespace optix;

Material BlinnPhongMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    material["ambientCoefficient"]->setFloat(mAmbientCoeff);
    material["diffuseCoefficient"]->setFloat(mDiffuseCoeff);
    material["specularCoefficient"]->setFloat(mSpecularCoeff);
    material["shininess"]->setFloat(mShininess);
    material["specularity"]->setFloat(mSpecularity);
    return material;
}


// Getter & Setter
// Color
const float3 &BlinnPhongMaterial::color() const
{
    return mColor;
}
float3 &BlinnPhongMaterial::color()
{
    return mColor;
}
void BlinnPhongMaterial::setColor(const float3 &color)
{
    mColor = color;
}

// Ambient Coefficient
const float &BlinnPhongMaterial::ambientCoeff() const
{
    return mAmbientCoeff;
}
float &BlinnPhongMaterial::ambientCoeff()
{
    return mAmbientCoeff;
}
void BlinnPhongMaterial::setAmbientCoeff(const float &ambientCoeff)
{
    mAmbientCoeff = ambientCoeff;
}

// Diffuse Coefficient
const float &BlinnPhongMaterial::diffuseCoeff() const
{
    return mDiffuseCoeff;
}
float &BlinnPhongMaterial::diffuseCoeff()
{
    return mDiffuseCoeff;
}
void BlinnPhongMaterial::setDiffuseCoeff(const float &diffuseCoeff)
{
    mDiffuseCoeff = diffuseCoeff;
}

// Specular Coefficient
const float &BlinnPhongMaterial::specularCoeff() const
{
    return mSpecularCoeff;
}
float &BlinnPhongMaterial::specularCoeff()
{
    return mSpecularCoeff;
}
void BlinnPhongMaterial::setSpecularCoeff(const float &specularCoeff)
{
    mSpecularCoeff = specularCoeff;
}

// Shininess
const float &BlinnPhongMaterial::shininess() const
{
    return mShininess;
}
float &BlinnPhongMaterial::shininess()
{
    return mShininess;
}
void BlinnPhongMaterial::setShininess(const float &shininess)
{
    mShininess = shininess;
}

// Specularity
const float &BlinnPhongMaterial::specularity() const
{
    return mSpecularity;
}
float &BlinnPhongMaterial::specularity()
{
    return mSpecularity;
}
void BlinnPhongMaterial::setSpecularity(const float &specularity)
{
    mSpecularity = specularity;
}


// Operator overload
bool operator!=(const BlinnPhongMaterial &mat1, const BlinnPhongMaterial &mat2)
{
    return(mat1.ambientCoeff() != mat2.ambientCoeff() || mat1.specularCoeff() != mat2.specularCoeff() || mat1.diffuseCoeff() != mat2.diffuseCoeff() ||
            mat1.color().x != mat2.color().x || mat1.color().y != mat2.color().y || mat1.color().z != mat2.color().z ||
            mat1.shininess() != mat2.shininess() || mat1.specularity() != mat2.specularity());
}

