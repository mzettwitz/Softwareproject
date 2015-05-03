#ifndef PROGRAM2_H
#define PROGRAM2_H

#include <optix.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sutil.h>
#include <cstdlib>
#include <iostream>
#include <optixu/optixpp_namespace.h>
#include <../cuda/commonStructs.h>
#include <optixu/optixu_math_namespace.h>

using namespace optix;

int program2(int argc, char* argv[]);
std::string ptxPath(const std::string &file);

Context createContext();
Material createMaterial(Context context);
Geometry createGeometry(Context context);
void createInstances(Context context, Geometry geometry, Material material);


#endif //PROGRAM2_H

