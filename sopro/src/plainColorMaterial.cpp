#include "../include/plainColorMaterial.h"

using namespace optix;

void PlainColorMaterial::setColor(const float3 &c)
{
    mColor = c;
}

Material PlainColorMaterial::createMaterial(Context context) const
{

    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    return material;
}

float3 PlainColorMaterial::color() const
{
    return mColor;
}

bool operator!=(const PlainColorMaterial &mat1, const PlainColorMaterial &mat2)
{
    return (mat1.color().x != mat2.color().x || mat1.color().y != mat2.color().y || mat1.color().z != mat2.color().z);
}
