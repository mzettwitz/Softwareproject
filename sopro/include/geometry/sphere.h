#ifndef SPHERE_H
#define SPHERE_H

#include "baseGeometry.h"

class Sphere : public BaseGeometry
{

public:
    // ------------------------CTor
    // ------------ Advanced CTor
    /*!
     * \brief Advanced Constructor for Sphere
     *
     * \param pos
     * specifies position of Sphere
     * \param intersect
     * specifies interectionProgram for areaPlane
     * \param boundingbox
     * specifies boundingboxProgram for areaPlane
     * \param path
     * specifies path to ptx files
     */
    Sphere(float3 pos) : BaseGeometry(pos,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu")
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
        mGeometryType = SPHERE;
    }

    Geometry createGeometry(Context context) const;

};

#endif //SPHERE_H
