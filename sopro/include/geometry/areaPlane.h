/*!
 * \file areaPlane.h
 * \brief
 *
 * limited plane
 *
 * \var mDimensions Float value for size of the plane
 * \var mPos Float3 3D coordinates for the center
 */


#ifndef AREAPLANE_H
#define AREAPLANE_H


#include "baseGeometry.h"

class AreaPlane : public BaseGeometry
{
private:
    float3 mPosition;
    float2 mDimensions;
public:
    /*!
     * \brief AreaPlane
     *
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
    AreaPlane(float3 pos,float2 dim) : BaseGeometry(pos,"areaPlaneIntersectionProgram","areaPlaneBoundingBoxProgram","areaPlane.cu"), mPosition(pos) , mDimensions(dim)
    {
        mGeometryType = AREAPLANE;
    }
    /*!
     * \brief createGeometry
     *
     * creates optixGeometry from set parameters
     * \param context
     * specifies used context
     * \return
     * returns optix::Geometry when created successfully
     */
    Geometry createGeometry(Context context) const;

    // Setter
    void setDimensions(float2 &dim);

    // Special getter for ATB
    const float2& dimensions() const;
    float2& dimensions();


};

#endif //AREAPLANE_H
