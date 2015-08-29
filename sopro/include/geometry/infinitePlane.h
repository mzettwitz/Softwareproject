#ifndef INFINITEPLANE_H
#define INFINITEPLANE_H

#include "baseGeometry.h"



class InfinitePlane : public BaseGeometry
{
private:
    float mHeight;

public:
    InfinitePlane(float height) : mHeight(height),
        BaseGeometry(make_float3(0.0f,0.0f,0.0f),"infinitePlaneIntersectionProgram","infinitePlaneBoundingBoxProgram","infinitePlane.cu")
    {
        mGeometryType = INFINITEPLANE;
    }
    Geometry createGeometry(Context context) const;

    // Setter
    void setHeight(const float h);

    // Special getter for ATB
    const float& height() const;
    float& height();
};

#endif //INFINITEPLANE_H
