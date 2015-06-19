#ifndef SCENE_H
#define SCENE_H

#include "sceneobject.h"
#include <optixpp_namespace.h>

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
    std::vector<SceneObject>        mSceneObjects;
    optix::GeometryGroup            mGeometryGroup;
    optix::Context                  mContext;
    unsigned int                    mWidth;
    unsigned int                    mHeight;
    Camera                          mCamera;

public:
                                    Scene();
    void                            trace(const Scene::Camera &camera);
    void                            initScene(const Scene::Camera &camera);
    void                            addSceneObject(const SceneObject &object);
    void                            addSceneObject(BaseGeometry *geometry, BaseMaterial *material, const std::string &name);
    void                            removeObject(const std::string &object);
    void                            removeObject(const unsigned int index);
    std::vector<SceneObject>*       getSceneObjects();
    SceneObject*                    getSceneObject(const std::string &name);
    SceneObject*                    getSceneObject(const unsigned int index);
    int                             getSceneObjectCount();   
    optix::Buffer                   getOutputBuffer();

private:
    void                            updateScene(const Scene::Camera &camera);
    void                            updateSceneObjects();
    void                            updateCamera(const Scene::Camera &camera);
    optix::Buffer                   createOutputBuffer(RTformat format);

};


#endif //SCENE_H
