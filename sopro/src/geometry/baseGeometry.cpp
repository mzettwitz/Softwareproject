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

void BaseGeometry::setRotation(const float3 &rot)
{
    mRot = rot;
    changed = true;
}

void BaseGeometry::setRotation(const float value, const short pos)
{
    changed = true;
    switch(pos)
    {
    case 0:
        mRot.x = value;
        break;
    case 1:
        mRot.y = value;
        break;
    case 2:
        mRot.z = value;
        break;
    }
}

const float3& BaseGeometry::rotation() const
{
    return mRot;
}

float3& BaseGeometry::rotation()
{
    return mRot;
}

void BaseGeometry::setScale(const float3 &scale)
{
    changed = true;
    mScale =  scale;
}

void BaseGeometry::setScale(const float value, const short pos)
{
    changed = true;
    switch(pos)
    {
    case 0 :
        mScale.x = value;
        break;
    case 1 :
        mScale.y = value;
        break;
    case 2:
        mScale.z = value;
        break;
    }
}

const float3& BaseGeometry::scale() const
{
    return mScale;
}

float3& BaseGeometry::scale()
{
    return mScale;
}
