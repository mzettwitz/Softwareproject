/*!
 * TODO: closest hit
 * anyhit, for shadows
 *
 */



#include "../include/material.h"

using namespace optix;

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
