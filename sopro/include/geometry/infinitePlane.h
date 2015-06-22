#ifndef INFINITEPLANE_H
#define INFINITEPLANE_H

#include "baseGeometry.h"



class InfinitePlane : public BaseGeometry
{
private:
    float mHeight;

public:
    InfinitePlane(float height) : mHeight(height),BaseGeometry(make_float3(0.0f,0.0f,0.0f),"infinitePlaneIntersectionProgram","infinitePlaneBoundingBoxProgram","infinitePlane.cu")
    {
        mGeometryType = INFINITEPLANE;
    }
    Geometry createGeometry(Context context) const;
};

#endif //INFINITEPLANE_H
