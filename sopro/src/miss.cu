#include <optix_world.h>

//color returned if no object hit
rtDeclareVariable(float3,missColor,,);
//raypayload for normal rays, see pinholeCamera.cu
struct PerRayData_radiance
{	//returning color
	float3 result;
	//not used now
	float importance;
	//recursionDepth
	int depth;
};
/*!
 * declare payload
 */
rtDeclareVariable(PerRayData_radiance,prd_radiance,rtPayload,);

/*!
 *\brief return missColor, if no object was hit
 */
RT_PROGRAM miss void()
{
	prd_radiance.result = missColor;
}
