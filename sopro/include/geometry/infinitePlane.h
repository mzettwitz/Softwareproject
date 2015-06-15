#ifndef INFINITEPLANE_H
#define INFINITEPLANE_H

#include "baseGeometry.h"



class infinitePlane : protected BaseGeometry
{
private:
    float mHeight;

public:
    infinitePlane(float height, std::string intersect,std::string boundingbox,std::string path) : mHeight(height),BaseGeometry(make_float3(0.0f,0.0f,0.0f),intersect,boundingbox,path)
    {
        mGeometryType = INFINITEPLANE;
    }
    Geometry createGeometry(Context context) const;
};

#endif //INFINITEPLANE_H
