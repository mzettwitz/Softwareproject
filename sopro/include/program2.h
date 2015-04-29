#ifndef PROGRAM2_H
#define PROGRAM2_H

#include "helpingHands.h"

#include <optix.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sutil.h>

int program2(int argc, char* argv[]);

void createContext(RTcontext* context, RTbuffer* buffer);
void createMaterial(RTcontext context, RTmaterial* material);
void createGeometry(RTContext context, RTGeometry* geom);
void createInstances(RTcontext context, RTgeometry geom, RTmaterial material);


#endif //PROGRAM2_H

