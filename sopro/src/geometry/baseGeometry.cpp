#include "../../include/geometry/baseGeometry.h"

//setter
void BaseGeometry::setPosition(const float3 &pos)
{
        mPos = pos;
        changed = true;

}

void BaseGeometry::setPosition(const float value, const short pos)
{
    changed = true;
    switch(pos)
    {
    case 0:
        mPos.x = value;
        break;
    case 1:
        mPos.y = value;
        break;
    case 2:
        mPos.z = value;
    default:
        break;
    }
}

//getter
const float3& BaseGeometry::position() const
{
    return mPos;
}
float3& BaseGeometry::position()
{
    return mPos;
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
