#include <optix_world.h>
#include "../include/structs.h"
//color returned if no object hit
rtDeclareVariable(float4,missColor,,);
//raypayload for normal rays, see pinholeCamera.cu

/*!
 * declare payload
 */
rtDeclareVariable(PerRayData_radiance,prd_radiance,rtPayload,);

/*!
 *\brief return missColor, if no object was hit
 */
RT_PROGRAM void miss ()
{
	prd_radiance.result = missColor;
}
