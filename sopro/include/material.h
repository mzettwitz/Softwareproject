/*! \file material.h
 * \brief A material header file.
 * \author Martin Zettwitz, 2015
 *
 * Contains simple basic attritutes.
 */


/*! \var float4 color
 * \brief Contains RGB-color information in a 4d float vector.
 *
 * RGB + alpha value
 */

/*! \fn Material()
 * \brief Advanced CTor with \param color as argument.
 * \return Instance of \class Material.
 */

/*! \fn void setColor(float4 newColor)
 * \brief  Simple setter for \var color to set new color Information.
 * \param newColor The new color to be set.
 */

/*! \fn float4 setColor()
 * \brief Simple getter for \var color.
 * \return float4 color information about the material.
 */

#pragma once

#include <commonStructs.h>

class Material {
private:
    float4 color;

public:
    Material();
    Material(float4 color);
    ~Material();
    void setColor(float4 newColor);
    float4 getColor();
};
