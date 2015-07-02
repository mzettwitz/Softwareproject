#include "../../include/material/phongMaterial.h"

using namespace optix;

Material PhongMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["ambientColor"]->setFloat(mAmbientColor.x,mAmbientColor.y,mAmbientColor.z);
    material["diffuseColor"]->setFloat(mDiffuseColor.x,mDiffuseColor.y,mDiffuseColor.z);
    material["specularColor"]->setFloat(mSpecularColor.x,mSpecularColor.y,mSpecularColor.z);
    material["ambientCoefficient"]->setFloat(mAmbientCoeff);
    material["diffuseCoefficient"]->setFloat(mDiffuseCoeff);
    material["specularCoefficient"]->setFloat(mSpecularCoeff);
    material["shininess"]->setFloat(mShininess);
    return material;
}


// Getter & Setter
// Ambient color
const float3 &PhongMaterial::ambientColor() const
{
    return mAmbientColor;
}
float3 &PhongMaterial::ambientColor()
{
    return mAmbientColor;
}
void PhongMaterial::setAmbientColor(const float3 &ambientColor)
{
    mAmbientColor = ambientColor;
}

//Diffuse color
const float3 &PhongMaterial::diffuseColor() const
{
    return mDiffuseColor;
}
float3& PhongMaterial::diffuseColor()
{
    return mDiffuseColor;
}
void PhongMaterial::setDiffuseColor(const float3 &diffuseColor)
{
    mDiffuseColor = diffuseColor;
}

// Specular Color
const float3 &PhongMaterial::specularColor() const
{
    return mSpecularColor;
}
float3& PhongMaterial::specularColor()
{
    return mSpecularColor;
}
void PhongMaterial::setSpecularColor(const float3 &specularColor)
{
    mSpecularColor = specularColor;
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

// Operator overload
bool operator!=(const PhongMaterial &mat1, const PhongMaterial &mat2)
{
    return(mat1.ambientCoeff() != mat2.ambientCoeff() || mat1.ambientColor().x != mat2.ambientColor().x || mat1.ambientColor().y != mat2.ambientColor().y || mat1.ambientColor().z != mat2.ambientColor().z || mat1.diffuseCoeff() != mat2.diffuseCoeff() || mat1.diffuseColor().x != mat2.diffuseColor().x ||mat1.diffuseColor().y !=mat2.diffuseColor().y || mat1.diffuseColor().z != mat2.diffuseColor().z || mat1.shininess() != mat2.shininess() || mat1.specularCoeff() != mat2.specularCoeff() || mat1.specularColor().x != mat2.specularColor().x || mat1.specularColor().y != mat2.specularColor().y || mat1.specularColor().z != mat2.specularColor().z);
}

