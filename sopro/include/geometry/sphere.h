#ifndef SPHERE_H
#define SPHERE_H

#include "baseGeometry.h"

class Sphere : public BaseGeometry
{
    float mRadius;
public:
    // ------------------------CTor
    // ------------ Advanced CTor
    /*!
     * \brief Advanced Constructor for Sphere
     *
     * \param pos
     * specifies position of Sphere
     * \param radius
     * specifies radius of Sphere
     * \param intersect
     * specifies interectionProgram for areaPlane
     * \param boundingbox
     * specifies boundingboxProgram for areaPlane
     * \param path
     * specifies path to ptx files
     */
    Sphere(float3 pos,float r) : mRadius(r),BaseGeometry(pos,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu")
    {
        mGeometryType = SPHERE;
    }

    //------------- Copy CTors
    // pass through
    /*!
     * \brief Simple copy CTor to pass through an existing \class Sphere object.
     *
     * \param in1 Smartpointer to the object you want to copy.
     */
    Sphere(const std::shared_ptr<BaseGeometry> in1) : BaseGeometry(in1->position(),"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu")
    {
        std::shared_ptr<Sphere> in = std::dynamic_pointer_cast<Sphere>(in1);
        mRadius = in->radius();
        mGeometryType = SPHERE;
    }
    // change position
    /*!
     * \brief Copy CTor to copy an existing \class Sphere object and change it's position.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param newPos The new position you want to setup in your new object
     */
    Sphere(const std::shared_ptr<BaseGeometry> in1, const float3 &newPos) :
        BaseGeometry(newPos,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu")
    {
        std::shared_ptr<Sphere> in = std::dynamic_pointer_cast<Sphere>(in1);
        mRadius = in->radius();
        mGeometryType = SPHERE;
    }
    // change radius
    /*!
     * \brief Copy CTor to copy an existing \class Sphere object and change it's radius.
     *
     * \param in1 Smartpointer to the object you want to copy.
     * \param newDim The new radius you want to setup in your new object
     */
    Sphere(const std::shared_ptr<BaseGeometry> in1, float newRadius) :
        mRadius(newRadius), BaseGeometry(in1->position(),"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu")
    {
        mGeometryType = SPHERE;
    }

    Geometry createGeometry(Context context) const;

    // Setter
    void setRadius(float r);

    // Special getter for ATB
    const float& radius() const;
    float& radius();
};

#endif //SPHERE_H
