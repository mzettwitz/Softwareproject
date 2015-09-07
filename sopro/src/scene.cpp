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
    mGroup = mContext->createGroup();
    mSceneObjects = std::make_shared<std::vector<std::shared_ptr<SceneObject>>>();
    mLights = std::make_shared<std::vector<PointLight>>();
}

Scene::~Scene()
{
    mGroup->destroy();
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
    mContext->setStackSize(4096);

    mWidth  = width;
    mHeight = height;

    PointLight l1;
    l1.color = make_float3(1.0f,1.0f,1.0f);
    l1.intensity = 1800.0f;
    l1.padding = 0;
    l1.position = make_float3(10.0f,20.0f,-30.0f);
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
    std::shared_ptr<Sphere> dummyGeom = std::make_shared<Sphere>(make_float3(0.0f,0.0f,0.0f));
    dummyGeom->setScale(make_float3(0.1f,0.1f,0.1f));
    std::shared_ptr<LambertMaterial> dummyMat = std::make_shared<LambertMaterial>(make_float3(1.0f,0.0f,0.0f));
    std::shared_ptr<SceneObject> dummy = std::make_shared<SceneObject>("dummy",dummyGeom,dummyMat);
    mSceneObjects->push_back(dummy);

    //pass geometry/material to optix
    mGroup->setChildCount(mSceneObjects->size());

    for(unsigned int i = 0;i < mSceneObjects->size();++i)
    {
        Transform t = mContext->createTransform();
        t->setMatrix(false,IdentityMatrix,IdentityMatrix);
        GeometryInstance gi = mContext->createGeometryInstance();
        gi->setMaterialCount(1);
        gi->setGeometry(mSceneObjects->at(i)->getGeometry()->createGeometry(mContext));
        gi->setMaterial(0,mSceneObjects->at(i)->getMaterial()->createMaterial(mContext));
        GeometryGroup gg = mContext->createGeometryGroup();
        gg->setChildCount(1);
        gg->setChild(0,gi);
        gg->setAcceleration(mContext->createAcceleration("Trbvh","Bvh"));
        t->setChild(gg);
        mGroup->setChild(0,t);

    }

    mGroup->setAcceleration(mContext->createAcceleration("Trbvh","Bvh"));

    mContext["topObject"]->set(mGroup);
    mContext["topShadower"]->set(mGroup);

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
    mGroup->setChildCount(mSceneObjects->size());
    GeometryInstance gi = mContext->createGeometryInstance();
    gi->setGeometry(object->getGeometry()->createGeometry(mContext));
    gi->setMaterialCount(1);
    gi->setMaterial(0,object->getMaterial()->createMaterial(mContext));

    GeometryGroup gg = mContext->createGeometryGroup();
    gg->setChildCount(1);
    gg->setChild(0,gi);
    gg->setAcceleration(mContext->createAcceleration("Trbvh","Bvh"));

    Transform t = mContext->createTransform();
    t->setChild(gg);
    t->setMatrix(0,IdentityMatrix,IdentityMatrix);

    mGroup->setChild(mSceneObjects->size()-1,t);

    gi->getGeometry()->markDirty();
    mGroup->getAcceleration()->markDirty();
}

void Scene::addSceneObject(std::shared_ptr<BaseGeometry> geometry, std::shared_ptr<BaseMaterial> material, const std::string &name)
{
    std::shared_ptr<SceneObject> object = std::make_shared<SceneObject>(name,geometry,material);
    mSceneObjects->push_back(object);
    mGroup->setChildCount(mSceneObjects->size());
    GeometryInstance gi = mContext->createGeometryInstance();
    gi->setGeometry(object->getGeometry()->createGeometry(mContext));
    gi->setMaterialCount(1);
    gi->setMaterial(0,object->getMaterial()->createMaterial(mContext));

    GeometryGroup gg = mContext->createGeometryGroup();
    gg->setChildCount(1);
    gg->setChild(0,gi);
    gg->setAcceleration(mContext->createAcceleration("Trbvh","Bvh"));

    Transform t = mContext->createTransform();
    t->setChild(gg);
    t->setMatrix(0,IdentityMatrix,IdentityMatrix);

    mGroup->setChild(mSceneObjects->size()-1,t);

    gi->getGeometry()->markDirty();
    mGroup->getAcceleration()->markDirty();
}

void Scene::removeObject(const std::string &object)
{
    for(int i = 0;i < mSceneObjects->size();++i)
    {
        if(mSceneObjects->at(i)->getName() == object)
        {
            mSceneObjects->erase(mSceneObjects->begin()+i);
            mGroup->removeChild(i);
            mGroup->getAcceleration()->markDirty();
            return;
        }

    }

}

void Scene::removeObject(const unsigned int index)
{
    if(index < mSceneObjects->size())
    {
        mSceneObjects->erase(mSceneObjects->begin()+index);
        mGroup->removeChild(index);
        mGroup->getAcceleration()->markDirty();
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
                    mGroup->getChild<Transform>(i)->getChild<GeometryGroup>()->getChild(0)->getMaterial(0)["color"]->setFloat(c.x,c.y,c.z);
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

                    Material m = mGroup->getChild<Transform>(i)->getChild<GeometryGroup>()->getChild(0)->getMaterial(0);
                    m["color"]->setFloat(c.x,c.y,c.z);
                    m["ambientCoefficient"]->setFloat(ambientCoeff);
                    m["diffuseCoefficient"]->setFloat(diffuseCoeff);
                    m["specularCoefficient"]->setFloat(specularCoeff);
                    m["specularity"]->setFloat(specularity);
                    m["shininess"]->setFloat(shininess);
                    break;
                }
                case BaseMaterial::GLASS : ;break;
                {
                    std::shared_ptr<GlassMaterial> glass = std::dynamic_pointer_cast<GlassMaterial>(mSceneObjects->at(i)->getMaterial());
                    float3 c = glass->color();
                    float shininess = glass->shininess();
                    float specularCoeff = glass->specularCoeff();

                    Material m = mGroup->getChild<Transform>(i)->getChild<GeometryGroup>()->getChild(0)->getMaterial(0);
                    m["color"]->setFloat(c.x,c.y,c.z);
                    m["shininess"]->setFloat(shininess);
                    m["specularCoeff"]->setFloat(specularCoeff);
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
                mGroup->getChild<Transform>(i)->getChild<GeometryGroup>()->getChild(0)->setMaterial(0,mSceneObjects->at(i)->getMaterial()->createMaterial(mContext));

            }
        }
        mSceneObjects->at(i)->updateGeometry();

        if(mSceneObjects->at(i)->isGeometryChanged())
        {

            //TODO split into translation rotation scaling
               Transform t = mGroup->getChild<Transform>(i);
               float3 pos = mSceneObjects->at(i)->getGeometry()->position();
               float3 rot = mSceneObjects->at(i)->getGeometry()->rotation();
               float3 scale = mSceneObjects->at(i)->getGeometry()->scale();
               const float trans[16] = {1,0,0,pos.x,
                                        0,1,0,pos.y,
                                        0,0,1,pos.z,
                                        0,0,0,1};
               Matrix4x4 transM(trans);

               const float rotX[16] = {1,0          ,0          ,0,
                                       0,static_cast<float>(cos(rot.x)) ,static_cast<float>(-sin(rot.x)),0,
                                       0,static_cast<float>(sin(rot.x)) ,static_cast<float>(cos(rot.x)) ,0,
                                       0,0          ,0          ,1};
               const float rotY[16] = {static_cast<float>(cos(rot.y)),0,static_cast<float>(sin(rot.y)),0,
                                       0,1,0,0,
                                       static_cast<float>(-sin(rot.y)),0,static_cast<float>(cos(rot.y)),0,
                                       0,0,0,1};
               const float rotZ[16] = {static_cast<float>(cos(rot.z)),static_cast<float>(-sin(rot.z)),0,0,
                                       static_cast<float>(sin(rot.z)),static_cast<float>(cos(rot.z)),0,0,
                                       0,0,1,0,
                                       0,0,0,1};
               Matrix4x4 rotXM(rotX);
               Matrix4x4 rotYM(rotY);
               Matrix4x4 rotZM(rotZ);

               Matrix4x4 rotM = rotXM * rotYM * rotZM;

               const float s[16] ={scale.x,0,0,0,
                                   0,scale.y,0,0,
                                   0,0,scale.z,0,
                                   0,0,0,1};
               Matrix4x4 scaleM(s);

               Matrix4x4 M = transM * scaleM * rotM;

               t->setMatrix(0,M.getData(),0);
               mGroup->getAcceleration()->markDirty();
               t->getChild<GeometryGroup>()->getAcceleration()->markDirty();
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
