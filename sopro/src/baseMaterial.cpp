#include "../include/baseMaterial.h"

void BaseMaterial::setPTXPath(const std::string &path)
{
    mPTXpath = std::string(sutilSamplesPtxDir()) + "/sopro_generated_" + path + ".ptx";
}

BaseMaterial::MaterialType BaseMaterial::getMaterialType() const
{
    return mMaterialType;
}
