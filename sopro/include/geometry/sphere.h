#ifndef SPHERE_H
#define SPHERE_H

#include "baseGeometry.h"

class Sphere : protected BaseGeometry
{

    float mRadius;
public:
    Sphere(float3 pos,float r,std::string intersect, std::string boundingbox, std::string path) : mRadius(r),BaseGeometry(pos,intersect,boundingbox,path)
    {
        mGeometryType = SPHERE;
    }
    Geometry createGeometry(Context context) const;
};

#endif //SPHERE_H
