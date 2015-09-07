#include "../../include/material/wardMaterial.h"

Material WardMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    material["diffuseCoeff"]->setFloat(mDiffuseCoeff);
    material["specularCoeff"]->setFloat(mSpecularCoeff);
    material["anisotropicFactorU"]->setFloat(mAnisotropicFactorU);
    material["anisotropicFactorV"]->setFloat(mAnisotropicFactorV);
    return material;
}
const float3& WardMaterial::color() const
{
    return mColor;
}

float3& WardMaterial::color()
{
    return mColor;
}

void WardMaterial::setColor(const float3 &color)
{
    mColor = color;
}

const float& WardMaterial::diffuseCoeff() const
{
    return mDiffuseCoeff;
}

float& WardMaterial::diffuseCoeff()
{
    return mDiffuseCoeff;
}

void WardMaterial::setDiffuseCoeff(const float &diffuseCoeff)
{
    mDiffuseCoeff = diffuseCoeff;
}

const float& WardMaterial::anistropicFactorU() const
{
    return mAnisotropicFactorU;
}

float& WardMaterial::anisotropicFactorU()
{
    return mAnisotropicFactorU;
}

void WardMaterial::setAnisotropicFactorU(const float &u)
{
    mAnisotropicFactorU = u;
}

const float& WardMaterial::anisotropicFactorV() const
{
    return mAnisotropicFactorV;
}

float& WardMaterial::anistropicFactorV()
{
    return mAnisotropicFactorV;
}

void WardMaterial::setAnistropicFactorV(const float &v)
{
    mAnisotropicFactorV = v;
}

const float& WardMaterial::specularCoeff() const
{
    return mSpecularCoeff;
}

float& WardMaterial::specularCoeff()
{
    return mSpecularCoeff;
}

void WardMaterial::setSpecularCoeff(const float &specularCoeff)
{
    mSpecularCoeff = specularCoeff;
}

