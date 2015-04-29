#ifndef PROGRAM2_H
#define PROGRAM2_H

#include <optix.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sutil.h>

int program2(int argc, char* argv[]);

void createContext(RTcontext* context, RTbuffer* buffer);
void createMaterial(RTcontext context, RTmaterial* material);
void createGeometry(RTContext context, RTGeometry* box);
void createInstances(RTcontext context, RTgeometry box, RTmaterial material);


#endif //PROGRAM2_H

