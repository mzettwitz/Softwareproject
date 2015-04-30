#include <optix_world.h>

rtDeclareVariable(float3,missColor,,);

struct PerRayData_radiance
{
	float3 result;
	float importance;
	int depth;
};

rtDeclareVariable(PerRayData_radiance,prd_radiance,rtPayload,);

RT_PROGRAM miss void()
{
	prd_radiance.result = missColor;
}
