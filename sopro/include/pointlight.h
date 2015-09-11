#pragma once

#include "../include/optixu/optixu_math_namespace.h"
#include <string>
#include <memory>
#include "../sopro/include/structs.h"

class PointLightClass
{
private:
    float3 mPosition;
    float3 mColor;
    float mIntensity;
    std::string mName;
    bool mLightChanged;

    void markLightAsChanged();

public:
    // CTor
    PointLightClass(const float3 & pos, const float3 &col, float inten, std::string name) :
        mPosition(pos), mColor(col), mIntensity(inten), mName(name){}

    PointLightClass(std::shared_ptr<PointLightClass> in) :
        mPosition(in->position()), mColor(in->color()), mIntensity(in->intensity()), mName(in->name()){}

    PointLightClass(const PointLight* in) :
        mPosition(in->position), mColor(in->color), mIntensity(in->intensity)
    {
        mName = "light";
    }

    PointLightClass(const PointLight* in, std::string name) :
        mPosition(in->position), mColor(in->color), mIntensity(in->intensity), mName(name){}

    // getter and setter
    void setPosition(const float3& pos);
    const float3& position() const;
    float3& position();

    void setPositionIdx(float pos, short idx);
    const float& positionIdx(short idx) const;
    float& positionIdx(short idx);


    void setColor(const float3& col);
    const float3& color() const;
    float3& color();

    void setIntensity(float inten);
    const float& intensity() const;
    float& intensity();

    std::string& name();

    // changed?
    bool isLightChanged();

};


