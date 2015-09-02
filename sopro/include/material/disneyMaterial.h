// don't forget to alter the sceneObject for setMaterial
/*! \file disneyMaterial.h
 *  \brief A disney material header file
 *  \author Martin Zettwitz, Michael Größler, 2015
 *
 *  \var mColor RGB color
 *  \var mMetallicness Float the metallic-ness, 0 = dielectric, 1 = metallic
 *  \var mSubsurface Float controls diffuse shape using a subsurface approximation
 *  \var mSpecular Float incident specular amount. This is in lieu of an explicit index-of-refraction
 *  \var mRoughness Float surface roughness, controls both diffuse and specular response
 *  \var mSpecularTint Float a concession for artistic control that tints incident specular towards the base color. Grazing specular is still achromatic
 *  \var mAnisotropic Float degree of anisotropy. This contols the aspect ratio of the specular highlight(0 = isotropic, 1 = maximally anistropic)
 *  \var mSheen Float an additional grazing component, primarily intended for cloth
 *  \var mSheenTint Float amount to tint sheen towards base color
 *  \var mClearcoat Float a sceond, special purpose  specular lobe
 *  \var mClearcoatGloss Float controls clearcoat glossiness, 0 = a "satin" appearance, 1 = a "gloss" appearance
 *
 */

#pragma once

#include "baseMaterial.h"
/*
using namespace optix;

class DisneyMaterial : public DisneyMaterial
{
private:
    float3  mColor;
    float   mMetallic;
    float   mSubsurface;
    float   mSpecular;
    float   mRoughness;
    float   mSpecularTint;
    float   mAnisotropic;
    float   mSheen;
    float   mSheenTint;
    float   mClearcoat;
    float   mClearcoatGloss;

public:*/
    //---------------------CTor
    //------------Advanced CTor
    /*! \brief CTor to generate \class DisneyMaterial object based on given attributes.
     *
     *  \param
     *
     *
     */

 //   DisneyMaterial() : mColor(make_float3(0.5f,0.5f,0.5f))
//};
