#include "../../include/material/wardMaterial.h"

Material WardMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    material["diffuseCoefficient"]->setFloat(mDiffuseCoeff);
    material["anisotropicX"]->setFloat(mX);
    material["anisotropicY"]->setFloat(mY);
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

const float& WardMaterial::x() const
{
    return mX;
}

float& WardMaterial::x()
{
    return mX;
}

void WardMaterial::setX(const float &x)
{
    mX = x;
}

const float& WardMaterial::y() const
{
    return mY;
}

float WardMaterial::y()
{
    return mY;
}

void WardMaterial::setY(const float &y)
{
    mY = y;
}

