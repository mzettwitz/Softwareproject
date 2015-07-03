#include "../../include/material/phongMaterial.h"

using namespace optix;

Material PhongMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["Color"]->setFloat(mColor.x,mColor.y,mColor.z);
    material["ambientCoefficient"]->setFloat(mAmbientCoeff);
    material["diffuseCoefficient"]->setFloat(mDiffuseCoeff);
    material["specularCoefficient"]->setFloat(mSpecularCoeff);
    material["shininess"]->setFloat(mShininess);
    material["specularity"]->setFloat(mSpecularity);
    return material;
}


// Getter & Setter
// Color
const float3 &PhongMaterial::color() const
{
    return mColor;
}
float3 &PhongMaterial::color()
{
    return mColor;
}
void PhongMaterial::setColor(const float3 &color)
{
    mColor = color;
}

// Ambient Coefficient
const float &PhongMaterial::ambientCoeff() const
{
    return mAmbientCoeff;
}
float &PhongMaterial::ambientCoeff()
{
    return mAmbientCoeff;
}
void PhongMaterial::setAmbientCoeff(float ambientCoeff)
{
    mAmbientCoeff = ambientCoeff;
}

// Diffuse Coefficient
const float &PhongMaterial::diffuseCoeff() const
{
    return mDiffuseCoeff;
}
float &PhongMaterial::diffuseCoeff()
{
    return mDiffuseCoeff;
}
void PhongMaterial::setDiffuseCoeff(float diffuseCoeff)
{
    mDiffuseCoeff = diffuseCoeff;
}

// Specular Coefficient
const float &PhongMaterial::specularCoeff() const
{
    return mSpecularCoeff;
}
float &PhongMaterial::specularCoeff()
{
    return mSpecularCoeff;
}
void PhongMaterial::setSpecularCoeff(float specularCoeff)
{
    mSpecularCoeff = specularCoeff;
}

// Shininess
const float &PhongMaterial::shininess() const
{
    return mShininess;
}
float &PhongMaterial::shininess()
{
    return mShininess;
}
void PhongMaterial::setShininess(float shininess)
{
    mShininess = shininess;
}

// Specularity
const float &PhongMaterial::specularity() const
{
    return mSpecularity;
}
float &PhongMaterial::specularity()
{
    return mSpecularity;
}
void PhongMaterial::setSpecularity(float specularity)
{
    mSpecularity = specularity;
}


// Operator overload
bool operator!=(const PhongMaterial &mat1, const PhongMaterial &mat2)
{
    return(mat1.ambientCoeff() != mat2.ambientCoeff() || mat1.specularCoeff() != mat2.specularCoeff() || mat1.diffuseCoeff() != mat2.diffuseCoeff() ||
            mat1.color().x != mat2.color().x || mat1.color().y != mat2.color().y || mat1.color().z != mat2.color().z ||
            mat1.shininess() != mat2.shininess() || mat1.specularity() != mat2.specularity());
}

