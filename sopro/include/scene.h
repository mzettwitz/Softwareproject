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

private:
    std::shared_ptr<std::vector<std::shared_ptr<SceneObject>>>        mSceneObjects;
    optix::GeometryGroup            mGeometryGroup;
    optix::Context                  mContext;
    unsigned int                    mWidth;
    unsigned int                    mHeight;
    Camera                          mCamera;

public:
                                    Scene();
                                    ~Scene();
    void                            trace(const Scene::Camera &camera);
    void                            initScene(const Scene::Camera &camera,int width, int height);
    void                            addSceneObject(std::shared_ptr<SceneObject> object);
    void                            addSceneObject(std::shared_ptr<BaseGeometry> geometry, std::shared_ptr<BaseMaterial> material, const std::string &name);
    void                            removeObject(const std::string &object);
    void                            removeObject(const unsigned int index);
    std::shared_ptr<std::vector<std::shared_ptr<SceneObject>>>   getSceneObjects();
    std::shared_ptr<SceneObject>    getSceneObject(const std::string &name);
    std::shared_ptr<SceneObject>    getSceneObject(const unsigned int index);
    int                             getSceneObjectCount();   
    optix::Buffer                   getOutputBuffer();
    void                            resizeBuffer(int width, int height);
    void                            setSceneEpsilon(float amount);

private:
    void                            updateScene(const Scene::Camera &camera);
    void                            updateSceneObjects();
    void                            updateCamera(const Scene::Camera &camera);
    optix::Buffer                   createOutputBuffer(RTformat format);

};


#endif //SCENE_H
