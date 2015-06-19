#include "../../include/geometry/areaPlane.h"

Geometry AreaPlane::createGeometry(Context context) const
{
    Geometry geometry = context->createGeometry();
    geometry->setPrimitiveCount(1);
    geometry->setBoundingBoxProgram(context->createProgramFromPTXFile(mPTXpath,mBoundingBoxProgram));
    geometry->setIntersectionProgram(context->createProgramFromPTXFile(mPTXpath,mIntersectionProgram));
    geometry["position"]->setFloat(mPos.x,mPos.y,mPos.z);
    geometry["dimensions"]->setFloat(mDimensions.x,mDimensions.y);

    return geometry;
}
