#include "../../include/geometry/infinitePlane.h"
#include <limits>

using namespace optix;

Geometry InfinitePlane::createGeometry(Context context) const
{
    Geometry geometry = context->createGeometry();
    geometry->setPrimitiveCount(1);
    geometry->setBoundingBoxProgram(context->createProgramFromPTXFile(mPTXpath,mBoundingBoxProgram));
    geometry->setIntersectionProgram(context->createProgramFromPTXFile(mPTXpath,mIntersectionProgram));
    geometry["plane"]->setFloat(std::numeric_limits<float>::min(),mHeight,std::numeric_limits<float>::max());
    return geometry;
}
