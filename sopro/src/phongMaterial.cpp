#include "../include/phongMaterial.h"

using namespace optix;

Material PhongMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["ambientColor"]->setFloat(mAmbientColor.x,mAmbientColor.y,mAmbientColor.z);
    material["diffuseColor"]->setFloat(mDiffuseColor.x,mDiffuseColor.y,mDiffuseColor.z);
    material["specularColor"]->setFloat(mSpecularColor.x,mSpecularColor.y,mSpecularColor.z);
    material["ambientCoefficient"]->setFloat(mAbientCoeff);
    material["diffuseCoefficient"]->setFloat(mDiffuseCoeff);
    material["specularCoefficient"]->setFloat(mSpecularCoeff);
    material["shininess"]->setFloat(mShininess);
    return material;
}


// Getter & Setter
float3 PhongMaterial::ambientColor() const
{
    return mAmbientColor;
}

void PhongMaterial::setAmbientColor(const float3 &ambientColor)
{
    mAmbientColor = ambientColor;
}

float3 PhongMaterial::diffuseColor() const
{
    return mDiffuseColor;
}

void PhongMaterial::setDiffuseColor(const float3 &diffuseColor)
{
    mDiffuseColor = diffuseColor;
}

float3 PhongMaterial::specularColor() const
{
    return mSpecularColor;
}

void PhongMaterial::setSpecularColor(const float3 &specularColor)
{
    mSpecularColor = specularColor;
}

float PhongMaterial::abientCoeff() const
{
    return mAbientCoeff;
}

void PhongMaterial::setAbientCoeff(float abientCoeff)
{
    mAbientCoeff = abientCoeff;
}

float PhongMaterial::diffuseCoeff() const
{
    return mDiffuseCoeff;
}

void PhongMaterial::setDiffuseCoeff(float diffuseCoeff)
{
    mDiffuseCoeff = diffuseCoeff;
}

float PhongMaterial::specularCoeff() const
{
    return mSpecularCoeff;
}

void PhongMaterial::setSpecularCoeff(float specularCoeff)
{
    mSpecularCoeff = specularCoeff;
}

float PhongMaterial::shininess() const
{
    return mShininess;
}

void PhongMaterial::setShininess(float shininess)
{
    mShininess = shininess;
}

bool operator!=(const PhongMaterial &mat1, const PhongMaterial &mat2)
{
    return(mat1.abientCoeff() != mat2.abientCoeff() || mat1.ambientColor().x != mat2.ambientColor().x || mat1.ambientColor().y != mat2.ambientColor().y || mat1.ambientColor().z != mat2.ambientColor().z || mat1.diffuseCoeff() != mat2.diffuseCoeff() || mat1.diffuseColor().x != mat2.diffuseColor().x ||mat1.diffuseColor().y !=mat2.diffuseColor().y || mat1.diffuseColor().z != mat2.diffuseColor().z || mat1.shininess() != mat2.shininess() || mat1.specularCoeff() != mat2.specularCoeff() || mat1.specularColor().x != mat2.specularColor().x || mat1.specularColor().y != mat2.specularColor().y || mat1.specularColor().z != mat2.specularColor().z);
}

