/*! \file light.h
 * \brief The header file for the basic light class.
 *
 * The basic light class represents a ray generating point light.
 */


/*! \var int dummy
 * \brief Dummy
 *
 * Info
 */

/*! \fn int dummyfunction
 * \brief dummy
 * \param dummy
 * \return dummmy
 */

#pragma once

#include <optix.h>
#include <commonStructs.h>

class Light{
private:
    float4 origin;
    float4 color;

public:
    Light();
    Light(float4 ori, float4 col);
    ~Light();
    void setOrigin(float4 newOrigin);
    void setColor(float4 newColor);
    float4 getOrigin();
    float4 getColor();
};
