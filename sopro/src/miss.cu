#include <optix_world.h>
#include "../include/structs.h"


//raypayload for normal rays, see pinholeCamera.cu


/*!
 *\brief return missColor
 * \var prd_radiance Information about incoming ray
 * \var missColor RGBA background color
 *
 * Set missColor to ray if no object was hitten by incoming ray
 */


rtDeclareVariable(float4,missColor,,);
rtDeclareVariable(PerRayData_radiance,prd_radiance,rtPayload,);

RT_PROGRAM void miss ()
{
	prd_radiance.result = missColor;
}
