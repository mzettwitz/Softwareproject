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
    float2 mDimensions;
public:
    // ------------------------CTor
    // ------------ Advanced CTor
    /*!
     * \brief Advanced Constructor for AreaPlane
     *
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

    //------------- Copy CTors
    // pass through
    /*!
     * \brief Simple copy CTor to pass through an existing \class AreaPlane object.
     *
     * \param in1 Smartpointer to the object you want to copy.
     */
    AreaPlane(const std::shared_ptr<BaseGeometry> in1) :
        BaseGeometry(in1->position(),"areaPlaneIntersectionProgram","areaPlaneBoundingBoxProgram","areaPlane.cu")
    {
        std::shared_ptr<AreaPlane> in = std::dynamic_pointer_cast<AreaPlane>(in1);
        mDimensions = in->dimensions();
        mGeometryType = AREAPLANE;
    }
    // change position
    /*!
     * \brief Copy CTor to copy an existing \class AreaPlane object and change it's position.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param newPos The new position you want to setup in your new object
     */
    AreaPlane(const std::shared_ptr<BaseGeometry> in1, const float3 &newPos) :
        BaseGeometry(newPos,"areaPlaneIntersectionProgram","areaPlaneBoundingBoxProgram","areaPlane.cu")
    {
        std::shared_ptr<AreaPlane> in = std::dynamic_pointer_cast<AreaPlane>(in1);
        mDimensions = in->dimensions();
        mGeometryType = AREAPLANE;
    }
    // change dimensions
    /*!
     * \brief Copy CTor to copy an existing \class AreaPlane object and change it's dimensions.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param newDim The new dimensions you want to setup in your new object
     */
    AreaPlane(const std::shared_ptr<BaseGeometry> in1, float newDim, short pos):
        BaseGeometry(in1->position(),"areaPlaneIntersectionProgram","areaPlaneBoundingBoxProgram","areaPlane.cu")
    {
        std::shared_ptr<AreaPlane> in = std::dynamic_pointer_cast<AreaPlane>(in1);
        if(pos == 0)
            mDimensions.x = newDim;
        else
            mDimensions.y = newDim;

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
    void setDimensionsX(float x);
    void setDimensionsY(float y);

    // Special getter for ATB
    const float2& dimensions() const;
    float2& dimensions();

    const float& dimensionsX() const;
    float& dimensionsX();

    const float& dimensionsY() const;
    float& dimensionsY();


};

#endif //AREAPLANE_H
