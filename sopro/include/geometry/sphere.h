#ifndef SPHERE_H
#define SPHERE_H

#include "baseGeometry.h"

class Sphere : public BaseGeometry
{

    float mRadius;
public:
    Sphere(float3 pos,float r) : mRadius(r),BaseGeometry(pos,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu")
    {
        mGeometryType = SPHERE;
    }
    Geometry createGeometry(Context context) const;
};

#endif //SPHERE_H
