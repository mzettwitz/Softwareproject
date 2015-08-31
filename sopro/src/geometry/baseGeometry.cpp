#include "../../include/geometry/baseGeometry.h"

//setter
void BaseGeometry::setPosition(const float3 &pos)
{
    mPos = pos;
    changed = true;
}

//getter
const float3& BaseGeometry::position() const
{
    return mPos;
}
float3& BaseGeometry::position()
{
    mPos;
}

void BaseGeometry::setBoundingBoxProgram(const std::string &boundingbox)
{
    mBoundingBoxProgram = boundingbox;
}

void BaseGeometry::setIntersectionProgram(const std::string &intersection)
{
    mIntersectionProgram = intersection;
}

void BaseGeometry::setPTXpath(const std::string &p)
{
    mPTXpath = std::string(sutilSamplesPtxDir()) + "/sopro_generated_" + p + ".ptx";
}

BaseGeometry::GeometryType BaseGeometry::getGeometryType() const
{
    return mGeometryType;
}

bool BaseGeometry::isChanged()
{
    if(changed)
    {
        changed = false;
        return true;
    }
    return false;
}
