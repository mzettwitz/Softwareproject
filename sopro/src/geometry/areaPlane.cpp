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

// Setter
void AreaPlane::setDimensions(float2 &dim)
{
    mDimensions = dim;
}

void AreaPlane::setDimensionsX(float x)
{
    mDimensions.x = x;
}

void AreaPlane::setDimensionsY(float y)
{
    mDimensions.y = y;
}

// Special getter for ATB
const float2& AreaPlane::dimensions() const
{
    return mDimensions;
}
float2& AreaPlane::dimensions()
{
    return mDimensions;
}

const float& AreaPlane::dimensionsX() const
{
    return mDimensions.x;
}
float& AreaPlane::dimensionsX()
{
    return mDimensions.x;
}

const float& AreaPlane::dimensionsY() const
{
    return mDimensions.y;
}
float& AreaPlane::dimensionsY()
{
    return mDimensions.y;
}


// Operator overload
bool operator!=(const AreaPlane &geom1, const AreaPlane &geom2)
{
    return(geom1.position().x != geom2.position().x || geom1.position().y != geom2.position().y || geom1.position().z != geom2.position().z ||
            geom1.dimensions().x != geom2.dimensions().x || geom1.dimensions().y != geom2.dimensions().y);
}

