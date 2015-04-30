/*!
 * TODO: closest hit
 * anyhit, for shadows
 *
 */



#include "../include/material.h"



using namespace optix;

struct PerRayData_shadow()
{
	float3 attenuation;
};

struct PerRayData_radiance()
{
	float3 result;
	float importance;
	int depth;
};

Material::Material(){
    this->color = make_float4(0,0,0,1);
}

Material::Material(float4 color){
    this->color = color;
}

Material::~Material(){}

void Material::setColor(float4 newColor){
    this->color = newColor;
}

float4 Material::getColor(){
    return this->color;
}


rtDeclareVariable(PerRayData_radiance,prd_radiance,rtPayload,);
rtDeclareVariable(PerRayData_shadow,prd_shadow,rtPayload,);
rtDeclareVariable(optix::Ray ray,rtCurrentRay,);


static __device__ void shadowed()
{
	//create ray from hit to light
	prd_shadow.attenuation = make_float3(0,0,0);
	rtTerminateRay();
}

static __device__ void shade()
{
}
