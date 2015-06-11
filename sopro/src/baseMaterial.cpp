#include "../include/baseMaterial.h"

void baseMaterial::setPTXPath(const std::string &path)
{
    mPTXpath = std::string(sutilSamplesPtxDir()) + "/sopro_generated_" + path + ".ptx";
}
