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

using namespace optix;

class baseGeometry
{
protected:
    float3 mPos;
    std::string mIntersectionProgram;
    std::string mBoundingBoxProgram;
    std::string mPTXpath;
public:
    virtual Geometry createGeometry(Context context) const = 0;
    void setPosition(const float3 &p);
    void setIntersectionProgram(const std::string &intersection);
    void setBoundingBoxProgram(const std::string &boundingbox);
    void setPTXpath(const std::string &p);
protected:
    baseGeometry(float3 pos, std::string intersect, std::string boundingbox,std::string path) : mPos(pos),mIntersectionProgram(intersect),mBoundingBoxProgram(boundingbox)
    {
        setPTXpath(path);
    }
};


#endif //BASEGEOMETRY_H
