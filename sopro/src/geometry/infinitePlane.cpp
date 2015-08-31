#include "../../include/geometry/infinitePlane.h"
#include <limits>

using namespace optix;

Geometry InfinitePlane::createGeometry(Context context) const
{
    Geometry geometry = context->createGeometry();
    geometry->setPrimitiveCount(1);
    geometry->setBoundingBoxProgram(context->createProgramFromPTXFile(mPTXpath,mBoundingBoxProgram));
    geometry->setIntersectionProgram(context->createProgramFromPTXFile(mPTXpath,mIntersectionProgram));
    geometry["plane"]->setFloat(0.2f,mHeight,0.2f);
    return geometry;
}

// Setter
void InfinitePlane::setHeight(const float h)
{
    mHeight = h;
    changed = true;
}

// Special getter for ATB
const float& InfinitePlane::height() const
{
    return mHeight;
}
float& InfinitePlane::height()
{
    return mHeight;
}

// Operator overload
bool operator!=(const InfinitePlane &geom1, const InfinitePlane &geom2)
{
    return(geom1.height() != geom2.height());
}
