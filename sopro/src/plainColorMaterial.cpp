#include "../include/plainColorMaterial.h"

using namespace optix;

void plainColorMaterial::setColor(const float3 &c)
{
    mColor = c;
}

Material plainColorMaterial::createMaterial(Context context) const
{

    Material material = context->createMaterial();
    material->setAnyHitProgram(1,context->createProgramFromPTXFile(mPTXpath,"anyhit_shadow"));
    material->setClosestHitProgram(0,context->createProgramFromPTXFile(mPTXpath,"closesthit_radiance"));
    material["color"]->setFloat(mColor.x,mColor.y,mColor.z);
    return material;
}

