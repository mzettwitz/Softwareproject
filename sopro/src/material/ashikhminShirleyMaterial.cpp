#include "../../include/material/ashikhminShirleyMaterial.h"

Material AshikhminShirleyMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    material["au"]->setFloat(mAnisotropicFactorU);
    material["av"]->setFloat(mAnisotropicFactorV);
    material["rs"]->setFloat(mSpecularCoeff);
    material["rd"]->setFloat(mDiffuseCoeff);
    return material;
}

const float3& AshikhminShirleyMaterial::color() const
{
    return mColor;
}

float3& AshikhminShirleyMaterial::color()
{
    return mColor;
}

void AshikhminShirleyMaterial::setColor(const float3 &color)
{
    mColor = color;
}

const float& AshikhminShirleyMaterial::anisotropicFactorU() const
{
    return mAnisotropicFactorU;
}

float& AshikhminShirleyMaterial::anisotropicFactorU()
{
    return mAnisotropicFactorU;
}

void AshikhminShirleyMaterial::setAnistropicFactorU(const float &u)
{
    mAnisotropicFactorU = u;
}

const float& AshikhminShirleyMaterial::anisotropicFactorV() const
{
    return mAnisotropicFactorV;
}

float& AshikhminShirleyMaterial::anisotropicFactorV()
{
    return mAnisotropicFactorV;
}

void AshikhminShirleyMaterial::setAnistropicFactorV(const float &v)
{
    mAnisotropicFactorV = v;
}

const float& AshikhminShirleyMaterial::diffuseCoeff() const
{
    return mDiffuseCoeff;
}

float& AshikhminShirleyMaterial::diffuseCoeff()
{
    return mDiffuseCoeff;
}

void AshikhminShirleyMaterial::setRd(const float &rd)
{
    mDiffuseCoeff = rd;
}

const float& AshikhminShirleyMaterial::specularCoeff() const
{
    return mSpecularCoeff;
}

float& AshikhminShirleyMaterial::specularCoeff()
{
    return mSpecularCoeff;
}

void AshikhminShirleyMaterial::setRs(const float &rs)
{
    mSpecularCoeff = rs;
}
