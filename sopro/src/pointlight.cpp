#include "../sopro/include/pointlight.h"

// changed?
void PointLightClass::markLightAsChanged()
{
    mLightChanged = true;
}

bool PointLightClass::isLightChanged()
{
    if(mLightChanged)
    {
        mLightChanged = false;
        return true;
    }
    return false;
}

// getter and setter
void PointLightClass::setPosition(const float3& pos)
{
    mPosition = pos;
    markLightAsChanged();
}
const float3& PointLightClass::position() const
{
    return mPosition;
}
float3& PointLightClass::position()
{
    return mPosition;
}

void PointLightClass::setPositionIdx(float pos, short idx)
{
    switch(idx)
    {
    case 0:
        mPosition.x = pos;
        markLightAsChanged();
        break;
    case 1:
        mPosition.y = pos;
        markLightAsChanged();
        break;
    case 2:
        mPosition.z = pos;
        markLightAsChanged();
        break;
    default:
        break;
    }
}
const float& PointLightClass::positionIdx(short idx) const
{
    switch(idx)
    {
    case 0:
        return mPosition.x;        
        break;
    case 1:
        return mPosition.y;
        break;
    case 2:
        return mPosition.z;
        break;
    default:
        break;
    }
}
float& PointLightClass::positionIdx(short idx)
{
    switch(idx)
    {
    case 0:
        return mPosition.x;
        break;
    case 1:
        return mPosition.y;
        break;
    case 2:
        return mPosition.z;
        break;
    default:
        break;
    }
}


void PointLightClass::setColor(const float3 &col)
{
    mColor = col;
    markLightAsChanged();
}
const float3& PointLightClass::color() const
{
    return mColor;
}
float3& PointLightClass::color()
{
    return mColor;
}

void PointLightClass::setIntensity(float inten)
{
    mIntensity = inten;
    markLightAsChanged();
}
const float& PointLightClass::intensity() const
{
    return mIntensity;
}
float& PointLightClass::intensity()
{
    return mIntensity;
}

std::string& PointLightClass::name()
{
    return mName;
}
