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
#include "../include/material/phongMaterial.h"
#include "../include/material/glassMaterial.h"
#include "../include/geometry/sphere.h"

Scene::Scene()
{
    mContext = optix::Context::create();
    mGeometryGroup = mContext->createGeometryGroup();
    mSceneObjects = std::make_shared<std::vector<std::shared_ptr<SceneObject>>>();
    mLights = std::make_shared<std::vector<PointLight>>();
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
    mContext["maxDepth"]->setUint(10u);
    mContext["sceneEpsilon"]->setFloat(1.5e-3f);
    mContext->setStackSize(8192);

    mWidth  = width;
    mHeight = height;

    PointLight l1;
    l1.color = make_float3(1.0f,0.5f,0.5f);
    l1.intensity = 1800.0f;
    l1.padding = 0;
    l1.position = make_float3(10.0f,20.0f,-60.0f);
    mLights->push_back(l1);

    optix::Buffer lightBuffer = mContext->createBuffer(RT_BUFFER_INPUT);
    lightBuffer->setFormat(RT_FORMAT_USER);
    lightBuffer->setElementSize(sizeof(PointLight));
    lightBuffer->setSize(mLights->size());

    PointLight* lBufferdata = static_cast<PointLight*>(lightBuffer->map());
    std::copy(mLights->begin(),mLights->end(),lBufferdata);


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


    mGeometryGroup->setAcceleration(mContext->createAcceleration("Trbvh","Bvh"));

    mContext["topObject"]->set(mGeometryGroup);
    mContext["topShadower"]->set(mGeometryGroup);

    mContext->validate();
    mContext->compile();
}

void Scene::updateScene(const Scene::Camera &camera)
{
    updateCamera(camera);
    updateSceneObjects();
    updateLights();
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
            bool t = mSceneObjects->at(i)->getMaterial()->isTypeChanged();
            if(!t)
            {
                switch(mSceneObjects->at(i)->getMaterial()->getMaterialType())
                {
                case BaseMaterial::LAMBERT :
                {
                    float3 c = std::dynamic_pointer_cast<LambertMaterial>(mSceneObjects->at(i)->getMaterial())->color();
                    mGeometryGroup->getChild(i)->getMaterial(0)["color"]->setFloat(c.x,c.y,c.z);
                    break;
                }
                case BaseMaterial::PHONG :
                {
                    std::shared_ptr<PhongMaterial> phong = std::dynamic_pointer_cast<PhongMaterial>(mSceneObjects->at(i)->getMaterial());
                    float3 c = phong->color();
                    float ambientCoeff = phong->ambientCoeff();
                    float diffuseCoeff = phong->diffuseCoeff();
                    float specularCoeff = phong->specularCoeff();
                    float shininess = phong->shininess();
                    float specularity = phong->specularity();

                    mGeometryGroup->getChild(i)->getMaterial(0)["color"]->setFloat(c.x,c.y,c.z);
                    mGeometryGroup->getChild(i)->getMaterial(0)["ambientCoefficient"]->setFloat(ambientCoeff);
                    mGeometryGroup->getChild(i)->getMaterial(0)["diffuseCoefficient"]->setFloat(diffuseCoeff);
                    mGeometryGroup->getChild(i)->getMaterial(0)["specularCoefficient"]->setFloat(specularCoeff);
                    mGeometryGroup->getChild(i)->getMaterial(0)["specularity"]->setFloat(specularity);
                    mGeometryGroup->getChild(i)->getMaterial(0)["shininess"]->setFloat(shininess);
                    break;
                }
                case BaseMaterial::GLASS : ;break;
                {
                    std::shared_ptr<GlassMaterial> glass = std::dynamic_pointer_cast<GlassMaterial>(mSceneObjects->at(i)->getMaterial());
                    float3 c = glass->color();
                    float shininess = glass->shininess();
                    float specularCoeff = glass->specularCoeff();

                    mGeometryGroup->getChild(i)->getMaterial(0)["color"]->setFloat(c.x,c.y,c.z);
                    mGeometryGroup->getChild(i)->getMaterial(0)["shininess"]->setFloat(shininess);
                    mGeometryGroup->getChild(i)->getMaterial(0)["specularCoeff"]->setFloat(specularCoeff);
                    break;
                }
                case BaseMaterial::DISNEY : ;break;
                case BaseMaterial::BLINNPHONG : ;break;
                case BaseMaterial::ASHIKHMINSHIRLEY : ;break;
                case BaseMaterial::WARD : ;break;
                case BaseMaterial::COOKTORRANCE : ;break;
                }

            }
            else
            {
                mGeometryGroup->getChild(i)->setMaterial(0,mSceneObjects->at(i)->getMaterial()->createMaterial(mContext));

            }
        }
        mSceneObjects->at(i)->updateGeometry();

        if(mSceneObjects->at(i)->isGeometryChanged())
        {
           if(mSceneObjects->at(i)->getGeometry()->getGeometryType() == BaseGeometry::SPHERE)
           {
               float3 position = mSceneObjects->at(i)->getGeometry()->position();
               mGeometryGroup->getChild(i)->getGeometry()["coordinates"]->setFloat(position.x,position.y,position.z);
               mGeometryGroup->getChild(i)->getGeometry()["radius"]->setFloat(std::dynamic_pointer_cast<Sphere>(mSceneObjects->at(i)->getGeometry())->radius());
           }
           else if(mSceneObjects->at(i)->getGeometry()->getGeometryType() == BaseGeometry::INFINITEPLANE)
           {
               mGeometryGroup->getChild(i)->getGeometry()["plane"]->setFloat(0.2f,std::dynamic_pointer_cast<InfinitePlane>(mSceneObjects->at(i)->getGeometry())->height(),0.2f);
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

void Scene::updateLights()
{
    Buffer lightBuffer = mContext["lights"]->getBuffer();
    RTsize numLights;
    lightBuffer->getSize(numLights);
    if(mLights->size() != numLights)
    {
        lightBuffer->setSize(mLights->size());
    }
    PointLight* lBufferdata = static_cast<PointLight*>(lightBuffer->map());
    for(unsigned int i = 0;i < mLights->size();++i)
    {
        lBufferdata[i].position = mLights->at(i).position;
        lBufferdata[i].color = mLights->at(i).color;
        lBufferdata[i].intensity = mLights->at(i).intensity;
    }

    lightBuffer->unmap();

}

void Scene::addLight(PointLight &light)
{
    mLights->push_back(light);
}

void Scene::addLight(const float3 &position, const float3 &color, const float intensity)
{
    PointLight l;
    l.color = color;
    l.padding = 0;
    l.position = position;
    l.intensity = intensity;
    mLights->push_back(l);
}

void Scene::removeLight(const unsigned int index)
{
    if(index < mLights->size())
    {
        mLights->erase(mLights->begin()+index);
    }
}

PointLight Scene::getLight(const unsigned int index)
{
    return mLights->at(index);
}

int Scene::getLightCount()
{
    return mLights->size();
}
