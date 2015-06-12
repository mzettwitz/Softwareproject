#include "../include/phongMaterial.h"

using namespace optix;

Material phongMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["ambientColor"]->setFloat(mAmbientColor.x,mAmbientColor.y,mAmbientColor.z);
    material["diffuseColor"]->setFloat(mDiffuseColor.x,mDiffuseColor.y,mDiffuseColor.z);
    material["specularColor"]->setFloat(mSpecularColor.x,mSpecularColor.y,mSpecularColor.z);
    material["shininess"]->setFloat(mShininess);
    return material;
}


// Getter & Setter
float3 phongMaterial::ambientColor() const
{
    return mAmbientColor;
}

void phongMaterial::setAmbientColor(const float3 &ambientColor)
{
    mAmbientColor = ambientColor;
}

float3 phongMaterial::diffuseColor() const
{
    return mDiffuseColor;
}

void phongMaterial::setDiffuseColor(const float3 &diffuseColor)
{
    mDiffuseColor = diffuseColor;
}

float3 phongMaterial::specularColor() const
{
    return mSpecularColor;
}

void phongMaterial::setSpecularColor(const float3 &specularColor)
{
    mSpecularColor = specularColor;
}

float phongMaterial::shininess() const
{
    return mShininess;
}

void phongMaterial::setShininess(float shininess)
{
    mShininess = shininess;
}


