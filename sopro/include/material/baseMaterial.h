#ifndef BASEMATERIAL_H
#define BASEMATERIAL_H

#include "../cuda/commonStructs.h"
#include "../structs.h"
#include <optix.h>
#include <optixu/optixu_math_namespace.h>
#include <optixu/optixpp_namespace.h>
#include <sutil.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "../cuda/commonStructs.h"
#include <vector>
#include "../AntTweakBar/include/AntTweakBar.h"
#include <memory>

using namespace optix;

class BaseMaterial
{
public:
    typedef enum
    {
        LAMBERT = 1,
        PHONG = 2,
        DISNEY = 3,
        GLASS = 4
    } MaterialType;

protected:
    std::string mPTXpath;
    bool mTypeChanged;
    MaterialType mMaterialType;

public :
    virtual Material createMaterial(Context context) const = 0;
    void setPTXPath(const std::string &path);
    MaterialType getMaterialType() const;
    bool isTypeChanged();
    void markTypeAsChanged();
};


#endif //BASEMATERIAL_H
