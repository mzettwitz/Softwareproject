#include "../../include/material/glassMaterial.h"

using namespace optix;

Material GlassMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z, mColor.w);
    material["refractiveIdx"]->setFloat(mRefractiveIdx);
    material["specularity"]->setFloat(mSpecularity);
    material["shininess"]->setFloat(mShininess);
    material["specularCoeff"]->setFloat(mSpecularCoeff);
    return material;
}


// Getter & Setter
// Color
const float4 &GlassMaterial::color() const
{
    return mColor;
}
float4 &GlassMaterial::color()
{
    return mColor;
}
void GlassMaterial::setColor(const float4 &c)
{
    mColor = c;
}

// Refractive index
const float &GlassMaterial::refractiveIdx() const
{
    return mRefractiveIdx;
}
float &GlassMaterial::refractiveIdx()
{
    return mRefractiveIdx;
}
void GlassMaterial::setRefractiveIdx(float idx)
{
    mRefractiveIdx = idx;
}

// Specularity
const float &GlassMaterial::specularity() const
{
    return mSpecularity;
}
float &GlassMaterial::specularity()
{
    return mSpecularity;
}
void GlassMaterial::setSpecularity(float spec)
{
    mSpecularity = spec;
}

// Shininess
const float &GlassMaterial::shininess() const
{
    return mShininess;
}
float &GlassMaterial::shininess()
{
    return mShininess;
}
void GlassMaterial::setShininess(float shine)
{
    mShininess = shine;
}

// Specular coefficient
const float &GlassMaterial::specularCoeff() const
{
    return mSpecularCoeff;
}
float &GlassMaterial::specularCoeff()
{
    return mSpecularCoeff;
}
void GlassMaterial::setSpecularCoeff(float specC)
{
    mSpecularCoeff = specC;
}

// Operator overload
bool operator!=(const GlassMaterial &mat1, const GlassMaterial &mat2)
{
    return(mat1.refractiveIdx() != mat2.refractiveIdx() ||
            mat1.color().x != mat2.color().x || mat1.color().y != mat2.color().y ||
            mat1.color().z != mat2.color().z || mat1.color().w != mat2.color().w);
}
