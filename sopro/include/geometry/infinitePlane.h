#ifndef INFINITEPLANE_H
#define INFINITEPLANE_H

#include "baseGeometry.h"



class InfinitePlane : public BaseGeometry
{
private:
    float mHeight;

public:
    // ------------------------CTor
    // ------------ Advanced CTor
    /*!
     * \brief Advanced Constructor for InfinitePlane
     *
     * \param height
     * specifies height of InfinitePlane
     * \param intersect
     * specifies interectionProgram for areaPlane
     * \param boundingbox
     * specifies boundingboxProgram for areaPlane
     * \param path
     * specifies path to ptx files
     */
    InfinitePlane(float height) : mHeight(height),
        BaseGeometry(make_float3(0.0f,0.0f,0.0f),"infinitePlaneIntersectionProgram","infinitePlaneBoundingBoxProgram","infinitePlane.cu")
    {
        mGeometryType = INFINITEPLANE;
        changed = false;
    }

    //------------- Copy CTors
    // pass through
    /*!
     * \brief Simple copy CTor to pass through an existing \class InfinitePlane object.
     *
     * \param in1 Smartpointer to the object you want to copy.
     */
    InfinitePlane(const std::shared_ptr<BaseGeometry> in1) :
        BaseGeometry(in1->position(),"infinitePlaneIntersectionProgram", "infinitePlaneBoundingBoxProgram", "infinitePlane.cu")
    {
        std::shared_ptr<InfinitePlane> in = std::dynamic_pointer_cast<InfinitePlane>(in1);
        mHeight = in->height();

        mGeometryType = INFINITEPLANE;

    }
    // change height
    /*!
     * \brief Copy CTor to copy an existing \class InfninitePlane object and change it's height.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param newHeight The new height you want to setup in your new object
     */
    InfinitePlane(const std::shared_ptr<BaseGeometry> in1, float newHeight) :
        mHeight(newHeight), BaseGeometry(in1->position(),"infinitePlaneIntersectionProgram", "infinitePlaneBoundingBoxProgram", "infinitePlane.cu")
    {
        mGeometryType = INFINITEPLANE;
    }


    Geometry createGeometry(Context context) const;

    // Setter
    void setHeight(const float h);

    // Special getter for ATB
    const float& height() const;
    float& height();
};

#endif //INFINITEPLANE_H
