/*!
 * TODO: closest hit
 * anyhit, for shadows
 *
 */

#include "sopro/include/material.h"

Material::Material(){
    this->color = float4(0,0,0,1);
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
