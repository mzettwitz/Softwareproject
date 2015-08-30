#ifndef SPHERE_H
#define SPHERE_H

#include "baseGeometry.h"

class Sphere : public BaseGeometry
{
    float3 mPosition;
    float mRadius;
public:
    Sphere(float3 pos,float r) : mPosition(pos), mRadius(r),BaseGeometry(pos,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu")
    {
        mGeometryType = SPHERE;
    }
    Geometry createGeometry(Context context) const;

    // Setter
    void setPosition(const float3 &pos);
    void setRadius(float r);

    // Special getter for ATB
    const float3& position() const;
    float3& position();

    const float& radius() const;
    float& radius();
};

#endif //SPHERE_H
