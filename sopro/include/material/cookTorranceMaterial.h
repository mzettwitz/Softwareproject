#ifndef COOKTORRANCEMATERIAL_H
#define COOKTORRANCEMATERIAL_H

#include "baseMaterial.h"

using namespace optix;


class CookTorranceMaterial : public BaseMaterial
{
private:
    float3 mColor;
    float mFresnelFactor;
    float mRoughness;
    float mReflectance;


public:

    CookTorranceMaterial(float3 color, float fresnelFactor, float roughness, float reflectance) : mColor(color), mFresnelFactor(fresnelFactor), mRoughness(roughness), mReflectance(reflectance)
    {
        mMaterialType = COOKTORRANCE;
        setPTXPath("cookTorranceMaterial.cu");
    }

    Material createMaterial(Context context) const override;
};


#endif
