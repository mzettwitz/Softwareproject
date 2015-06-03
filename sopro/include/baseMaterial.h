#ifndef BASEMATERIAL_H
#define BASEMATERIAL_H

#include "../cuda/commonStructs.h"
#include "../include/structs.h"
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

using namespace optix;

class baseMaterial
{

protected:
    std::string mPTXpath;
public :
    virtual Material createMaterial(Context context) const = 0;
    void setPTXPath(const std::string &path);

};


#endif //BASEMATERIAL_H
