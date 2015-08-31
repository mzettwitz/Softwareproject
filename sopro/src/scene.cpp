#include "../include/scene.h"
#include <../cuda/commonStructs.h>
#include <optixu_math_namespace.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>
#include "../sutil/sutil.h"
#include "../include/program2.h"
#include "../../sutil/OptixMesh.h"

Scene::Scene()
{
    mContext = optix::Context::create();
    mGeometryGroup = mContext->createGeometryGroup();
    mSceneObjects = std::make_shared<std::vector<std::shared_ptr<SceneObject>>>();
}

Scene::~Scene()
{
    mGeometryGroup->destroy();
    mContext->destroy();
}

void Scene::trace(const Scene::Camera &camera)
{
    updateScene(camera);
    float3 eye = mCamera.position;
    float3 lookat = mCamera.direction+mCamera.position;
    float3 up = make_float3(0,1,0);
    float fov = 45.0f;
    float aspectRatio = float(mWidth)/float(mHeight);
    float3 u,v,w;

    sutilCalculateCameraVariables(&eye.x,&lookat.x,&up.x,fov,aspectRatio,&u.x,&v.x,&w.x);
    //update Camera
    mContext["eye"]->setFloat(eye);
    mContext["U"]->setFloat(u);
    mContext["V"]->setFloat(v);
    mContext["W"]->setFloat(w);

    optix::Buffer buffer = mContext["outputBuffer"]->getBuffer();
    RTsize bufferWidth, bufferHeight;
    buffer->getSize(bufferWidth,bufferHeight);


    mContext->launch(0,bufferWidth,bufferHeight);
}

void Scene::initScene(const Scene::Camera &camera,int width, int height)
{
    //specify context
    mContext->setRayTypeCount(2);
    mContext->setEntryPointCount(1);
    mContext["radianceRayType"]->setUint(0u);
    mContext["shadowRayType"]->setUint(1u);
  //  mContext["reflectanceRayType"]->setUint(2u);
    mContext["maxDepth"]->setUint(20u);
    mContext["sceneEpsilon"]->setFloat(1.5e-3f);
    mContext->setStackSize(4096);

    mWidth  = width;
    mHeight = height;

    PointLight lights[] = {
        {make_float3(10.0f,10.0f,-4.0f),make_float3(2.0f,1.0f,1.0f),250.0f,0},
        {make_float3(-4.0f,10.0f,5.0f),make_float3(1.0f,1.0f,0.0f),400.0f,0},
        {make_float3(-6.0,10.0f,-3.0f),make_float3(0.1f,0.6,1.0f),500.0f,0}
    };

    optix::Buffer lightBuffer = mContext->createBuffer(RT_BUFFER_INPUT);
    lightBuffer->setFormat(RT_FORMAT_USER);
    lightBuffer->setElementSize(sizeof(PointLight));
    lightBuffer->setSize(sizeof(lights)/sizeof(lights[0]));

    std::memcpy(lightBuffer->map(),lights,sizeof(lights));
    lightBuffer->unmap();
    mContext["lights"]->set(lightBuffer);

    mContext["outputBuffer"]->setBuffer(mContext->createBuffer(RT_BUFFER_OUTPUT,RT_FORMAT_FLOAT4,mWidth,mHeight));
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

    float3 eye = mCamera.position;
    float3 lookat = mCamera.direction+mCamera.position;
    float3 up = make_float3(0,1,0);
    float fov = 45.0f;
    float aspectRatio = float(mWidth)/float(mHeight);
    float3 u,v,w;

    sutilCalculateCameraVariables(&eye.x,&lookat.x,&up.x,fov,aspectRatio,&u.x,&v.x,&w.x);
    //update Camera
    mContext["eye"]->setFloat(eye);
    mContext["U"]->setFloat(u);
    mContext["V"]->setFloat(v);
    mContext["W"]->setFloat(w);

    //create dummy for whatever
    std::shared_ptr<Sphere> dummyGeom = std::make_shared<Sphere>(make_float3(0.0f,0.0f,0.0f),0.1f);
    std::shared_ptr<LambertMaterial> dummyMat = std::make_shared<LambertMaterial>(make_float3(1.0f,0.0f,0.0f));
    std::shared_ptr<SceneObject> dummy = std::make_shared<SceneObject>("dummy",dummyGeom,dummyMat);
    mSceneObjects->push_back(dummy);



    //pass geometry/material to optix
    mGeometryGroup->setChildCount(mSceneObjects->size());

    for(unsigned int i = 0;i < mSceneObjects->size();++i)
    {
        GeometryInstance gi = mContext->createGeometryInstance();
        gi->setMaterialCount(1);
        gi->setGeometry(mSceneObjects->at(i)->getGeometry()->createGeometry(mContext));
        gi->setMaterial(0,mSceneObjects->at(i)->getMaterial()->createMaterial(mContext));
        mGeometryGroup->setChild(i,gi);
    }


    mGeometryGroup->setAcceleration(mContext->createAcceleration("NoAccel","NoAccel"));

    mContext["topObject"]->set(mGeometryGroup);
    mContext["topShadower"]->set(mGeometryGroup);

    mContext->validate();
    mContext->compile();
}

void Scene::updateScene(const Scene::Camera &camera)
{
    updateCamera(camera);
    updateSceneObjects();
}

void Scene::addSceneObject(std::shared_ptr<SceneObject> object)
{
    mSceneObjects->push_back(object);
    mGeometryGroup->setChildCount(mSceneObjects->size());
    GeometryInstance gi = mContext->createGeometryInstance();
    gi->setGeometry(object->getGeometry()->createGeometry(mContext));
    gi->setMaterialCount(1);
    gi->setMaterial(0,object->getMaterial()->createMaterial(mContext));

    mGeometryGroup->setChild(mSceneObjects->size()-1,gi);

    gi->getGeometry()->markDirty();
    mGeometryGroup->getAcceleration()->markDirty();
}

void Scene::addSceneObject(std::shared_ptr<BaseGeometry> geometry, std::shared_ptr<BaseMaterial> material, const std::string &name)
{
    std::shared_ptr<SceneObject> object = std::make_shared<SceneObject>(name,geometry,material);
    mSceneObjects->push_back(object);

    mGeometryGroup->setChildCount(mSceneObjects->size());
    GeometryInstance gi = mContext->createGeometryInstance();
    gi->setGeometry(object->getGeometry()->createGeometry(mContext));
    gi->setMaterialCount(1);
    gi->setMaterial(0,object->getMaterial()->createMaterial(mContext));
    mGeometryGroup->setChild(mSceneObjects->size()-1,gi);

    gi->getGeometry()->markDirty();
    mGeometryGroup->getAcceleration()->markDirty();
}

void Scene::removeObject(const std::string &object)
{
    for(int i = 0;i < mSceneObjects->size();++i)
    {
        if(mSceneObjects->at(i)->getName() == object)
        {
            mSceneObjects->erase(mSceneObjects->begin()+i);
            mGeometryGroup->removeChild(i);
            return;
        }

    }
    mGeometryGroup->getAcceleration()->markDirty();
}

void Scene::removeObject(const unsigned int index)
{
    if(index < mSceneObjects->size())
    {
        mSceneObjects->erase(mSceneObjects->begin()+index);
        mGeometryGroup->removeChild(index);
        mGeometryGroup->getAcceleration()->markDirty();
        return;
    }

    printf("index out of bounds");
}

void Scene::updateSceneObjects()
{

    for(int i = 0;i < mSceneObjects->size();++i)
    {
        if(mSceneObjects->at(i)->isMaterialChanged())
        {

            mGeometryGroup->getChild(i)->setMaterial(0,mSceneObjects->at(i)->getMaterial()->createMaterial(mContext));
        }
        mSceneObjects->at(i)->updateGeometry();
        if(mSceneObjects->at(i)->isGeometryChanged())
        {
           if(mSceneObjects->at(i)->getGeometry()->getGeometryType() == BaseGeometry::SPHERE)
           {
               float3 position = mSceneObjects->at(i)->getGeometry()->position();
               float radius = std::dynamic_pointer_cast<Sphere>(mSceneObjects->at(i)->getGeometry())->radius();
               mGeometryGroup->getChild(i)->getGeometry()["coordinates"]->setFloat(position.x,position.y,position.z,radius);
           }
           else if(mSceneObjects->at(i)->getGeometry()->getGeometryType() == BaseGeometry::INFINITEPLANE)
           {
               mGeometryGroup->getChild(i)->getGeometry()["plane"]->setFloat(10000.0f,std::dynamic_pointer_cast<InfinitePlane>(mSceneObjects->at(i)->getGeometry())->height(),10000.0f);
           }
           else if(mSceneObjects->at(i)->getGeometry()->getGeometryType() == BaseGeometry::AREAPLANE)
           {
               //do something
           }
           else if(mSceneObjects->at(i)->getGeometry()->getGeometryType() == BaseGeometry::MESH)
           {
               //do something
           }

           mGeometryGroup->getChild(i)->getGeometry()->markDirty();
           mGeometryGroup->getAcceleration()->markDirty();
        }
    }

}

void Scene::updateCamera(const Scene::Camera &camera)
{
    mCamera.position = camera.position;
    mCamera.direction = camera.direction;
    mCamera.right = camera.right;
}

optix::Buffer Scene::createOutputBuffer(RTformat format)
{
    optix::Buffer buffer;

    buffer = mContext->createBuffer(RT_BUFFER_OUTPUT,format,mWidth,mHeight);

    return buffer;
}

optix::Buffer Scene::getOutputBuffer()
{
    return mContext["outputBuffer"].get()->getBuffer();
}

std::shared_ptr<SceneObject> Scene::getSceneObject(const unsigned int index)
{
    return (mSceneObjects->at(index));
}

std::shared_ptr<SceneObject> Scene::getSceneObject(const std::string &name)
{
    if(&name == nullptr)
    {
        return nullptr;
    }

    for(unsigned int i = 0;i < mSceneObjects->size();++i)
    {
        if(mSceneObjects->at(i)->getName() == name)
        {
            return mSceneObjects->at(i);
        }
    }

    return nullptr;
}

std::shared_ptr<std::vector<std::shared_ptr<SceneObject>>> Scene::getSceneObjects()
{
    return mSceneObjects;
}

int Scene::getSceneObjectCount()
{
    return mSceneObjects->size();
}

void Scene::resizeBuffer(int width,int height)
{
    mWidth = width;
    mHeight = height;
    mContext["outputBuffer"]->getBuffer()->setSize(mWidth,mHeight);
}

void Scene::setSceneEpsilon(float amount)
{
    mContext["sceneEpsilon"]->setFloat(amount + mContext["sceneEpsilon"]->getFloat());
}
