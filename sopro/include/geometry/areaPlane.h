/*!
 * \file areaPlane.h
 * \brief
 *
 * limited plane
 *
 */


#ifndef AREAPLANE_H
#define AREAPLANE_H


#include "baseGeometry.h"

class AreaPlane : protected BaseGeometry
{
private:
    /*!
     * \brief mDimensions
     * specifies size of plane
     */
    float2 mDimensions;
public:
    /*!
     * \brief areaPlane
     * Constructor for areaPlane
     * \param pos
     * specifies position of areaPlane
     * \param dim
     * specifies size of areaPlane
     * \param intersect
     * specifies interectionProgram for areaPlane
     * \param boundingbox
     * specifies boundingboxProgram for areaPlane
     * \param path
     * specifies path to ptx files
     */
    AreaPlane(float3 pos,float2 dim) : BaseGeometry(pos,"areaPlaneIntersectionProgram","areaPlaneBoundingBoxProgram","areaPlane.cu"), mDimensions(dim)
    {
        mGeometryType = AREAPLANE;
    }
    /*!
     * \brief createGeometry
     * creates optixGeometry from set parameters
     * \param context
     * specifies used context
     * \return
     * returns optix::Geometry when created successfully
     */
    Geometry createGeometry(Context context) const;
};

#endif //AREAPLANE_H
