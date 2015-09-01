#include "../../include/material/baseMaterial.h"

void BaseMaterial::setPTXPath(const std::string &path)
{
    mPTXpath = std::string(sutilSamplesPtxDir()) + "/sopro_generated_" + path + ".ptx";
}

BaseMaterial::MaterialType BaseMaterial::getMaterialType() const
{
    return mMaterialType;
}

bool BaseMaterial::isTypeChanged()
{
    if(mTypeChanged)
    {
        mTypeChanged = false;
        return true;
    }
    return false;
}

void BaseMaterial::markTypeAsChanged()
{
    mTypeChanged = true;
}
