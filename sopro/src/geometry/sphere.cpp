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
