#include "../../include/geometry/sphere.h"

using namespace optix;

Geometry Sphere::createGeometry(Context context) const
{
    Geometry geometry = context->createGeometry();
    geometry->setPrimitiveCount(1);
    geometry->setBoundingBoxProgram(context->createProgramFromPTXFile(mPTXpath,mBoundingBoxProgram));
    geometry->setIntersectionProgram(context->createProgramFromPTXFile(mPTXpath,mIntersectionProgram));
    geometry["coordinates"]->setFloat(mPos.x,mPos.y,mPos.z,mRadius);

    return geometry;
}

// Setter

void Sphere::setRadius(float r)
{
    mRadius = r;
}

// Special getter for ATB
const float& Sphere::radius() const
{
    return mRadius;
}
float& Sphere::radius()
{
    return mRadius;
}

// Operator overload
bool operator!=(const Sphere &geom1, const Sphere &geom2)
{
    return(geom1.position().x != geom2.position().x || geom1.position().y != geom2.position().y || geom1.position().z != geom2.position().z ||
            geom1.radius() != geom2.radius());
}
