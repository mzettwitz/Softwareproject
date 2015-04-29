#include "sopro/include/light.h"

Light::Light(){
    this->color = float4(1,1,1,1);
    this->origin = float4(0,0,0,0);
}

Light::Light(float4 ori, float4 col){
    this->origin = ori;
    this->color = col;
}

Light::~Light(){}

void Light::setOrigin(float4 newOrigin){
    this->origin = newOrigin;
}

void Light::setColor(float4 newColor){
    this->color = newColor;
}

float4 Light::getOrigin(){
    return this->origin;
}

float4  Light::getColor(){
    return this->color;
}
