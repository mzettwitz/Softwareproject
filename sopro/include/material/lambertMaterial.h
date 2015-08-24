/*! \file lambertMaterial.h
 * \brief A Lambert material header file.
 * \author Martin Zettwitz, Michael Größler, 2015
 *
 * Contains basic attributes like color for materials and shading based on Lambert.
 *
 * \var mColor RGB color
 * \var prd_radiance Information about traced ray hit
 * \var prd_shadow Information about shadow attenuation
 * \var ray Incoming camera ray
 * \var shadowRayType Type ID of the shadow ray
 * \var radianceRayType Type ID of the traced ray
 * \var sceneEpsilon Safty distance to avoid self intersections
 * \var topShadower Top Shadowing object in object tree
 * \var lights Lights of the Scene
 * \var intersectionDistance Distance from ray origin to intersection point
 */


#pragma once

#include "baseMaterial.h"

using namespace optix;




class LambertMaterial : public BaseMaterial
{
    float3 mColor;

public :
    //--------------------------CTor
    //------------- Advanced CTor
    /*!
     * \brief CTor to generate a \class LambertMaterial object based on a given color.
     *
     * \param c RGB color information for mColor.
     */
    LambertMaterial(const float3 &c) : mColor(c)
    {
        mMaterialType = LAMBERT;
        setPTXPath("lambertMaterial.cu");
    }

    //--------------- CTor for material conversion
    // Glass
    /*!
     * \brief CTor to generate a \class LambertMaterial object based on a given color.
     *
     * \note Useful for conversion from \class GlassMaterial.
     *
     * \param col RGBA color information for mColor.
     */
    LambertMaterial(const float4 &col)
    {
        mColor = make_float3(col.x, col.y, col.z);
        mMaterialType = LAMBERT;
        setPTXPath("lambertMaterial.cu");
    }

    Material createMaterial(Context context) const override;

    // Setter
    void setColor(const float3 &c);

    // Special getter for ATB
    const float3& color() const;
    float3& color();

};


