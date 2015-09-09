#include "../include/scene.h"
#include <../cuda/commonStructs.h>
#include <optixu_math_namespace.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include "../sutil/sutil.h"
#include "../include/program2.h"
#include "../../sutil/OptixMesh.h"
#include "../include/material/phongMaterial.h"
#include "../include/material/glassMaterial.h"
#include "../include/material/ashikhminShirleyMaterial.h"
#include "../include/material/blinnPhongMaterial.h"
#include "../include/material/cookTorranceMaterial.h"
#include "../include/material/wardMaterial.h"
#include "../include/geometry/sphere.h"
#include "../include/random.h"

void genRndSeeds(unsigned int width, unsigned int height, Buffer &b);

Scene::Scene()
{
    mFrameNumber = 0u;
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
    mContext["maxDepth"]->setUint(5u);
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

    /********************AA*********************************/

    mContext["frameNumber"]->setUint(mFrameNumber);

    Buffer variance_sum_buffer = mContext->createBuffer(RT_BUFFER_INPUT_OUTPUT | RT_BUFFER_GPU_LOCAL,RT_FORMAT_FLOAT4,mWidth,mHeight);
    std::memset(variance_sum_buffer->map(),0,mWidth * mHeight * sizeof(float4));
    variance_sum_buffer->unmap();
    mContext["varianceSumBuffer"]->set( variance_sum_buffer );

    Buffer variance_sum2_buffer = mContext->createBuffer( RT_BUFFER_INPUT_OUTPUT | RT_BUFFER_GPU_LOCAL,
                                                          RT_FORMAT_FLOAT4,
                                                          mWidth, mHeight );
    std::memset( variance_sum2_buffer->map(), 0, mWidth*mHeight*sizeof(float4) );
    variance_sum2_buffer->unmap();
    mContext["varianceSum2Buffer"]->set( variance_sum2_buffer );

    // Sample count buffer
    Buffer num_samples_buffer = mContext->createBuffer( RT_BUFFER_INPUT_OUTPUT | RT_BUFFER_GPU_LOCAL,
                                                        RT_FORMAT_UNSIGNED_INT,
                                                        mWidth, mHeight );
    std::memset( num_samples_buffer->map(), 0, mWidth*mHeight*sizeof(unsigned int) );
    num_samples_buffer->unmap();
    mContext["numSamplesBuffer"]->set( num_samples_buffer);

    // RNG seed buffer
    Buffer m_rnd_seeds = mContext->createBuffer( RT_BUFFER_INPUT_OUTPUT | RT_BUFFER_GPU_LOCAL,
                                         RT_FORMAT_UNSIGNED_INT,
                                         mWidth, mHeight );
    genRndSeeds( mWidth, mHeight,m_rnd_seeds );
    mContext["randomSeeds"]->set( m_rnd_seeds );

    /*****************************AA***************************/




    mContext["outputBuffer"]->setBuffer(mContext->createBuffer(RT_BUFFER_OUTPUT,RT_FORMAT_UNSIGNED_BYTE4,mWidth,mHeight));
    std::string usedPTXPath(ptxPath("pinholeCamera_AA.cu"));

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
    mContext["frameNumber"]->setUint(mFrameNumber);
    updateCamera(camera);
    updateSceneObjects();
    updateLights();
    mFrameNumber++;
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
    resetFrameNumber();
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
    resetFrameNumber();
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
            resetFrameNumber();
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
        resetFrameNumber();
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
                case BaseMaterial::BLINNPHONG :
                {
                    std::shared_ptr<BlinnPhongMaterial> phong = std::dynamic_pointer_cast<BlinnPhongMaterial>(mSceneObjects->at(i)->getMaterial());
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
                case BaseMaterial::ASHIKHMINSHIRLEY :
                {
                    std::shared_ptr<AshikhminShirleyMaterial> m = std::dynamic_pointer_cast<AshikhminShirleyMaterial>(mSceneObjects->at(i)->getMaterial());
                    float3 color = m->color();
                    float u = m->anisotropicFactorU();
                    float v = m->anisotropicFactorV();
                    float spec = m->specularCoeff();
                    float diff = m->diffuseCoeff();

                    Material a = mGroup->getChild<Transform>(i)->getChild<GeometryGroup>()->getChild(0)->getMaterial(0);
                    a["color"]->setFloat(color.x,color.y,color.z);
                    a["anisotropicFactorU"]->setFloat(u);
                    a["anisotropicFactorV"]->setFloat(v);
                    a["specularCoeff"]->setFloat(spec);
                    a["diff"]->setFloat(diff);
                    break;
                }
                case BaseMaterial::WARD :
                {
                    std::shared_ptr<WardMaterial> w = std::dynamic_pointer_cast<WardMaterial>(mSceneObjects->at(i)->getMaterial());
                    float3 color = w->color();
                    float u = w->anisotropicFactorU();
                    float v = w->anisotropicFactorV();
                    float diff = w->diffuseCoeff();
                    float spec = w->specularCoeff();

                    Material m = mGroup->getChild<Transform>(i)->getChild<GeometryGroup>()->getChild(0)->getMaterial(0);
                    m["color"]->setFloat(color.x,color.y,color.z);
                    m["anisotropicFactorU"]->setFloat(u);
                    m["anisotropicFactorV"]->setFloat(v);
                    m["diffuseCoeff"]->setFloat(diff);
                    m["specularCoeff"]->setFloat(spec);
                    ;break;
                }
                case BaseMaterial::COOKTORRANCE :
                {
                    std::shared_ptr<CookTorranceMaterial> c = std::dynamic_pointer_cast<CookTorranceMaterial>(mSceneObjects->at(i)->getMaterial());
                    float3 color = c->color();
                    float diff = c->diffuseCoeff();
                    float spec = c->specularCoeff();
                    float fresnel = c->fresnelFactor();
                    float roughness = c->roughness();
                    float refl = c->reflectance();

                    Material m = mGroup->getChild<Transform>(i)->getChild<GeometryGroup>()->getChild(0)->getMaterial(0);
                    m["color"]->setFloat(color.x,color.y,color.z);
                    m["diffuseCoeff"]->setFloat(diff);
                    m["specularCoeff"]->setFloat(spec);
                    m["fresnelFactor"]->setFloat(fresnel);
                    m["roughness"]->setFloat(roughness);
                    m["reflectance"]->setFloat(refl);
                    ;break;
                }
                case BaseMaterial::DISNEY : ;break; //TODO
                }

            }
            else
            {
                mGroup->getChild<Transform>(i)->getChild<GeometryGroup>()->getChild(0)->setMaterial(0,mSceneObjects->at(i)->getMaterial()->createMaterial(mContext));

            }
            resetFrameNumber();
        }
        mSceneObjects->at(i)->updateGeometry();

        if(mSceneObjects->at(i)->isGeometryChanged())
        {

            //TODO split into translation rotation scaling
               Transform t = mGroup->getChild<Transform>(i);
               float3 pos = mSceneObjects->at(i)->getGeometry()->position();
               float4 rot = mSceneObjects->at(i)->getGeometry()->rotation();
               float3 scale = mSceneObjects->at(i)->getGeometry()->scale();

               //translate
               const float tr[16] = {1,0,0,pos.x,
                                    0,1,0,pos.y,
                                    0,0,1,pos.z,
                                    0,0,0,1};
               Matrix4x4 transM(tr);

               //rotate, using quaternions
               float a = rot.z;
               float b = rot.y;
               float c = rot.x;
               float d = rot.w;

               const float r[16] =  { 1 - 2 * (c * c+ d* d),2*(b * c - a * d),      2*(b * d + a * c),      0,
                                      2 *(b * c + a * d),   1-2 * (d * d + b * b),  2 * (c * d - a * b),    0,
                                      2 * (b * d - a * c),  2 * (c * d + a * b),    1 - 2 * (b * b + c * c),0,
                                      0,                    0,                      0,                      1};

               Matrix4x4 rotM(r);
               //scale
               const float s[16] ={scale.x, 0,      0,      0,
                                   0,       scale.y,0,      0,
                                   0,       0,      scale.z,0,
                                   0,       0,      0,      1};
               Matrix4x4 scaleM(s);

               //set modelMatrix
               Matrix4x4 M = transM * rotM * scaleM;
               //pass to transform
               t->setMatrix(0,M.getData(),0);
               //mark dirty, otherwise no update
               mGroup->getAcceleration()->markDirty();
               t->getChild<GeometryGroup>()->getAcceleration()->markDirty();
               resetFrameNumber();
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
    mContext["varianceSumBuffer"]->getBuffer()->setSize(mWidth,mHeight);
    mContext["varianceSum2Buffer"]->getBuffer()->setSize(mWidth,mHeight);
    mContext["numSamplesBuffer"]->getBuffer()->setSize(mWidth,mHeight);
    mContext["randomSeeds"]->getBuffer()->setSize(mWidth,mHeight);
    resetFrameNumber();
}

void Scene::setSceneEpsilon(float amount)
{
    mContext["sceneEpsilon"]->setFloat(amount + mContext["sceneEpsilon"]->getFloat());
    resetFrameNumber();
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
    resetFrameNumber();
}

void Scene::addLight(PointLight &light)
{
    mLights->push_back(light);
    resetFrameNumber();
}

void Scene::addLight(const float3 &position, const float3 &color, const float intensity)
{
    PointLight l;
    l.color = color;
    l.padding = 0;
    l.position = position;
    l.intensity = intensity;
    mLights->push_back(l);
    resetFrameNumber();
}

void Scene::removeLight(const unsigned int index)
{
    if(index < mLights->size())
    {
        mLights->erase(mLights->begin()+index);
    }
    resetFrameNumber();
}

PointLight Scene::getLight(const unsigned int index)
{
    return mLights->at(index);
}

int Scene::getLightCount()
{
    return mLights->size();
}


void genRndSeeds( unsigned int width, unsigned int height,Buffer &b )
{
  unsigned int* seeds = static_cast<unsigned int*>( b->map() );
  fillRandBuffer( seeds, width*height );
  b->unmap();
}

void Scene::passFrameNumber(bool &changed)
{
    if(changed)
    {
        resetFrameNumber();
        changed = false;
    }
}

void Scene::resetFrameNumber()
{
    mFrameNumber = 0u;
}
