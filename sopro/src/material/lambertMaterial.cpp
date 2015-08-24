#include "../../include/material/lambertMaterial.h"

using namespace optix;

Material LambertMaterial::createMaterial(Context context) const
{

    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    return material;
}


// Getter and setter
void LambertMaterial::setColor(const float3 &c)
{
    mColor = c;
}

const float3& LambertMaterial::color() const
{
    return mColor;
}

float3& LambertMaterial::color()
{
    return mColor;
}

// operator overload
bool operator!=(const LambertMaterial &mat1, const LambertMaterial &mat2)
{
    return (mat1.color().x != mat2.color().x || mat1.color().y != mat2.color().y || mat1.color().z != mat2.color().z);
}

