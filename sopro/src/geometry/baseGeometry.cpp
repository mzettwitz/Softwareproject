#include "../../include/geometry/baseGeometry.h"

void baseGeometry::setPosition(const float3 &p)
{
    mPos = p;
}

void baseGeometry::setBoundingBoxProgram(const std::string &boundingbox)
{
    mBoundingBoxProgram = boundingbox;
}

void baseGeometry::setIntersectionProgram(const std::string &intersection)
{
    mIntersectionProgram = intersection;
}

void baseGeometry::setPTXpath(const std::string &p)
{
    mPTXpath = std::string(sutilSamplesPtxDir()) + "/sopro_generated_" + p + ".ptx";
}


