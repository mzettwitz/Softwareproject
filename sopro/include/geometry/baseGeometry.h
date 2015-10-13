#ifndef BASEGEOMETRY_H
#define BASEGEOMETRY_H

#include <optix.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sutil.h>
#include <cstdlib>
#include <iostream>
#include <optixu/optixpp_namespace.h>
#include <../cuda/commonStructs.h>
#include <optixu/optixu_math_namespace.h>
#include <vector>
#include <memory>

using namespace optix;

class BaseGeometry
{
public:
    typedef enum
    {
        SPHERE = 1,
        MESH = 2,
        INFINITEPLANE = 3,
        AREAPLANE = 4
    } GeometryType;
protected:
    float3 mPos;
    float4 mRot;
    float3 mScale;
    bool changed;
    std::string mIntersectionProgram;
    std::string mBoundingBoxProgram;
    std::string mPTXpath;

    GeometryType mGeometryType;
public:
    virtual Geometry createGeometry(Context context) const = 0;
    void setIntersectionProgram(const std::string &intersection);
    void setBoundingBoxProgram(const std::string &boundingbox);
    void setPTXpath(const std::string &p);
    GeometryType getGeometryType() const;
    bool isChanged();

    // Setter
    void setPosition(const float3 &pos);
    void setPosition(const float value, const short pos);

    void setRotation(const float4 &rot);

    void setScale(const float3 &scale);
    void setScale(const float value, const short pos);

    // Special getter for ATB
    const float3& position() const;
    float3& position();

    const float4& rotation() const;
    float4& rotation();

    const float3& scale() const;
    float3& scale();


protected:
    BaseGeometry(float3 pos, std::string intersect, std::string boundingbox,std::string path) :
        mPos(pos),mRot(make_float4(1,0,0,0)),mScale(make_float3(1,1,1)),
        mIntersectionProgram(intersect),mBoundingBoxProgram(boundingbox),changed(false)
    {
        setPTXpath(path);
    }
};


#endif //BASEGEOMETRY_H
