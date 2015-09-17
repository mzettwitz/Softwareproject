#include "../../include/material/ashikhminShirleyMaterial.h"

Material AshikhminShirleyMaterial::createMaterial(Context context) const
{
    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    material["anisotropicFactorU"]->setFloat(mAnisotropicFactorU);
    material["anisotropicFactorV"]->setFloat(mAnisotropicFactorV);
    material["specularCoeff"]->setFloat(mSpecularCoeff);
    material["diffuseCoeff"]->setFloat(mDiffuseCoeff);
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

void AshikhminShirleyMaterial::setAnisotropicFactorU(const float &u)
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

void AshikhminShirleyMaterial::setAnisotropicFactorV(const float &v)
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

void AshikhminShirleyMaterial::setDiffuseCoeff(const float &diffuseCoeff)
{
    mDiffuseCoeff = diffuseCoeff;
}

const float& AshikhminShirleyMaterial::specularCoeff() const
{
    return mSpecularCoeff;
}

float& AshikhminShirleyMaterial::specularCoeff()
{
    return mSpecularCoeff;
}

void AshikhminShirleyMaterial::setSpecularCoeff(const float &specularCoeff)
{
    mSpecularCoeff = specularCoeff;
}

// Operator overload
bool operator!=(const AshikhminShirleyMaterial &mat1, const AshikhminShirleyMaterial &mat2)
{
    return(mat1.anisotropicFactorU() != mat2.anisotropicFactorU() || mat1.anisotropicFactorV() != mat2.anisotropicFactorV() ||
            mat1.diffuseCoeff() != mat2.diffuseCoeff() || mat1.specularCoeff() != mat2.specularCoeff() ||
            mat1.color().x != mat2.color().x || mat1.color().y != mat2.color().y || mat1.color().z != mat2.color().z);
}
