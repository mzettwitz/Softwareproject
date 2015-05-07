#ifndef AREAPLANE_H
#define AREAPLANE_H


#include "baseGeometry.h"

class areaPlane : protected baseGeometry
{
private:
    float2 mDimensions;
public:
    areaPlane(float3 pos,float2 dim,std::string intersect,std::string boundingbox,std::string path) : baseGeometry(pos,intersect,boundingbox,path), mDimensions(dim)
    {}

    Geometry createGeometry(Context context) const;
};

#endif //AREAPLANE_H
