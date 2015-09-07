#include "../../include/material/cookTorranceMaterial.h"

Material CookTorranceMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    material["diffuseCoefficient"]->setFloat(mDiffuseCoeff);
    material["specularCoefficient"]->setFloat(mSpecularCoeff);
    material["fresnelFactor"]->setFloat(mFresnelFactor);
    material["roughness"]->setFloat(mRoughness);
    material["reflectance"]->setFloat(mReflectance);
    return material;
}

const float3& CookTorranceMaterial::color() const
{
    return mColor;
}

float3& CookTorranceMaterial::color()
{
    return mColor;
}

void CookTorranceMaterial::setColor(const float3 &color)
{
    mColor = color;
}

const float& CookTorranceMaterial::diffuseCoeff() const
{
    return mDiffuseCoeff;
}

float& CookTorranceMaterial::diffuseCoeff()
{
    return mDiffuseCoeff;
}

void CookTorranceMaterial::setDiffuseCoeff(const float &diffuseCoeff)
{
    mDiffuseCoeff = diffuseCoeff;
}

const float& CookTorranceMaterial::fresnelFactor() const
{
    return mFresnelFactor;
}

float& CookTorranceMaterial::fresnelFactor()
{
    return mFresnelFactor;
}

void CookTorranceMaterial::setFresnelFactor(const float &fresnelFactor)
{
    mFresnelFactor = fresnelFactor;
}

const float& CookTorranceMaterial::roughness() const
{
    return mRoughness;
}

float& CookTorranceMaterial::roughness()
{
    return mRoughness;
}

void CookTorranceMaterial::setRoughness(const float &roughness)
{
    mRoughness = roughness;
}

const float& CookTorranceMaterial::reflectance() const
{
    return mReflectance;
}

float& CookTorranceMaterial::reflectance()
{
    return mReflectance;
}

void CookTorranceMaterial::setReflectance(const float &reflectance)
{
    mReflectance = reflectance;
}

const float& CookTorranceMaterial::specularCoeff() const
{
    return mSpecularCoeff;
}

float& CookTorranceMaterial::specularCoeff()
{
    return mSpecularCoeff;
}

void CookTorranceMaterial::setSpecularCoeff(const float &specularCoeff)
{
    mSpecularCoeff = specularCoeff;
}
