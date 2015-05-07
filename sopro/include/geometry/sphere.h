#ifndef SPHERE_H
#define SPHERE_H

#include "baseGeometry.h"

class sphere : protected baseGeometry
{

    float mRadius;
public:
    sphere(float3 pos,float r,std::string intersect, std::string boundingbox, std::string path) : mRadius(r),baseGeometry(pos,intersect,boundingbox,path)
    {}
    Geometry createGeometry(Context context) const;
};

#endif //SPHERE_H
