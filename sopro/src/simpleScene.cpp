#include "../include/simpleScene.h"
#include <../cuda/commonStructs.h>
#include <optixu_math_namespace.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>
#include "../sutil/sutil.h"
#include "../include/program2.h"

SimpleScene::SimpleScene()
{
    mContext = Context::create();
    std::cout << "Scene constructed" << std::endl;
}

void SimpleScene::initScene(SimpleScene::Camera &camera)
{
    mContext->setRayTypeCount(2);
    mContext->setEntryPointCount(1);

    mContext["radiance_ray_type"]->setUint(0u);
    mContext["shadow_ray_type"]->setUint(1u);
    mContext["sceneEpsilon"]->setFloat(1.e-3f);
    mContext["maxDepth"]->setUint(10u);

    mWidth = 800;
    mHeight = 800;
    mContext["outputBuffer"]->set(createOutputBuffer(RT_FORMAT_FLOAT4,mWidth,mHeight));

    BasicLight light;

    light.color = optix::make_float3(1.0f,1.0f,1.0f);
    light.pos = optix::make_float3(100.f,100.f,-40.f);
    light.casts_shadow = 1;
    light.padding = 0;

    optix::Buffer lightBuffer = mContext->createBuffer(RT_BUFFER_INPUT,RT_FORMAT_USER,mWidth,mHeight);
    lightBuffer->setElementSize(sizeof(BasicLight));
    lightBuffer->setSize(1);
    std::memcpy(lightBuffer->map(),&light,sizeof(light));
    lightBuffer->unmap();
    mContext["lights"]->set(lightBuffer);

    std::string usedPTXPath(ptxPath("pinholeCamera.cu"));

    Program rayGenerationProgram = mContext->createProgramFromPTXFile(usedPTXPath,"pinholeCamera");
    mContext->setRayGenerationProgram(0,rayGenerationProgram);

    Program exceptionProgram = mContext->createProgramFromPTXFile(usedPTXPath,"exception");
    mContext->setExceptionProgram(0,exceptionProgram);
    mContext["excpetionColor"]->setFloat(1.0f,0.0f,0.0f,1.0f);
    //MissProgram
    usedPTXPath = ptxPath("miss.cu");
    Program missProgram = mContext->createProgramFromPTXFile(usedPTXPath,"miss");
    mContext->setMissProgram(0,missProgram);
    mContext["missColor"]->setFloat(0.3f,0.5f,0.8f,1.0f);


    //will be replaced in trace
    mContext["eye"]->setFloat(0,0,0);
    mContext["U"]->setFloat(0,0,0);
    mContext["V"]->setFloat(0,0,0);
    mContext["W"]->setFloat(0,0,0);

    updateGeometry();

    mContext->validate();
    mContext->compile();

}

optix::Buffer SimpleScene::createOutputBuffer(RTformat format, unsigned int width, unsigned int height)
{
    Buffer buffer;

    buffer = mContext->createBuffer(RT_BUFFER_OUTPUT,format,width,height);

    return buffer;
}

optix::Buffer SimpleScene::getOutputBuffer()
{
    return mContext["outputBuffer"]->getBuffer();
}

void SimpleScene::trace(SimpleScene::Camera &camera)
{
    //update Camera
    mContext["eye"]->setFloat(camera.position);
    mContext["U"]->setFloat(camera.direction);
    mContext["V"]->setFloat((camera.right));
    mContext["W"]->setFloat(cross(camera.direction,camera.right));

    optix::Buffer buffer = mContext["outputBuffer"]->getBuffer();
    RTsize bufferWidth, bufferHeight;
    buffer->getSize(bufferWidth,bufferHeight);

    //update Geometry

    mContext->launch(0,bufferWidth,bufferHeight);
}

void SimpleScene::updateGeometry()
{
    std::vector<Geometry> geom;
    std::vector<Material> mat;

    sphere s(make_float3(0.0f,1.0f,0.0f),1.0f,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu");
    geom.push_back(s.createGeometry(mContext));
    plainColorMaterial sphereMaterial(make_float3(0.8f,0.4f,0.1f),"plainColorMaterial.cu");
    mat.push_back(sphereMaterial.createMaterial(mContext));

    //create sphere
    sphere s2(make_float3(2.0f,1.2f,0.0f),1.2f,"sphereIntersectionProgram","sphereBoundingBoxProgram","sphere.cu");
    geom.push_back(s2.createGeometry(mContext));
    plainColorMaterial sphereMaterial2(make_float3(1.0f,0.2f,0.6f),"plainColorMaterial.cu");
    mat.push_back(sphereMaterial2.createMaterial(mContext));

    //create groundplane
    infinitePlane plane(0.0f,"infinitePlaneIntersectionProgram","infinitePlaneBoundingBoxProgram","infinitePlane.cu");
    geom.push_back(plane.createGeometry(mContext));
    plainColorMaterial planeMaterial(make_float3(0.2f,0.3f,0.4f),"plainColorMaterial.cu");
    mat.push_back(planeMaterial.createMaterial(mContext));

    createInstances(mContext,geom,mat);

}

// Getter
optix::Context SimpleScene::get_mContext(){
    return mContext;
}


