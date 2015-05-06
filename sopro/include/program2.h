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
#include <vector>
using namespace optix;

int program2(int argc, char* argv[]);
std::string ptxPath(const std::string &file);

Context createContext();
Material createSphereMaterial(Context context);
Material createPlaneMaterial(Context context);
Geometry createSphereGeometry(Context context);
Geometry createPlaneGeometry(Context context);
void createInstances(Context context, std::vector<Geometry> geometry, std::vector<Material> material);


#endif //PROGRAM2_H

