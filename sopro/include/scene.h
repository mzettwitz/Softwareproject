#ifndef SCENE_H
#define SCENE_H

#include "sceneobject.h"
#include <optixpp_namespace.h>
#include <memory>
#include <vector>

class Scene
{
public:
    struct Camera
    {
        Camera(){}
        Camera(optix::float3 &pos,optix::float3 &dir,optix::float3 &rig): position(pos),direction(dir),right(rig)
        {}
        optix::float3 position;
        optix::float3 direction;
        optix::float3 right;
    };

    const float IdentityMatrix[16] = {1,0,0,0,
                         0,1,0,0,
                         0,0,1,0,
                         0,0,0,1};

private:
    std::shared_ptr<std::vector<std::shared_ptr<SceneObject>>>      mSceneObjects;
    std::shared_ptr<std::vector<PointLight>>       mLights;
    optix::Group                    mGroup;
    optix::Context                  mContext;
    unsigned int                    mWidth;
    unsigned int                    mHeight;
    Camera                          mCamera;
    unsigned int                    mFrameNumber;

public:
                                    Scene();
                                    ~Scene();
    void                            trace(const Scene::Camera &camera);
    void                            initScene(const Scene::Camera &camera,int width, int height);
    void                            addSceneObject(std::shared_ptr<SceneObject> object);
    void                            addSceneObject(std::shared_ptr<BaseGeometry> geometry, std::shared_ptr<BaseMaterial> material, const std::string &name);
    void                            addLight(PointLight &light);
    void                            addLight(const float3 &position, const float3 &color,const float intensity);
    void                            removeObject(const std::string &object);
    void                            removeObject(const unsigned int index);
    void                            removeLight(const unsigned int index);
    std::shared_ptr<std::vector<std::shared_ptr<SceneObject>>>   getSceneObjects();
    std::shared_ptr<std::vector<PointLight>>    getLights();
    std::shared_ptr<SceneObject>    getSceneObject(const std::string &name);
    std::shared_ptr<SceneObject>    getSceneObject(const unsigned int index);
    PointLight                      getLight(const unsigned int index);
    int                             getSceneObjectCount();
    int                             getLightCount();
    optix::Buffer                   getOutputBuffer();
    void                            resizeBuffer(int width, int height);
    void                            setSceneEpsilon(float amount);
    void                            passFrameNumber(bool &changed);

private:
    void                            updateScene(const Scene::Camera &camera);
    void                            updateSceneObjects();
    void                            updateLights();
    void                            updateCamera(const Scene::Camera &camera);
    optix::Buffer                   createOutputBuffer(RTformat format);
    void                            resetFrameNumber();
    void                            genRandomSeeds(unsigned int width, unsigned int height, Buffer &b);

};


#endif //SCENE_H
