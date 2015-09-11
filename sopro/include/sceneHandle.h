#ifndef SCENEHANDLE_H
#define SCENEHANDLE_H

#include <optixu/optixpp_namespace.h>
#include <string>
#include <memory>
#include "../include/scene.h"

using namespace optix;

class SceneHandle
{
private:
    unsigned int            mHeight;
    unsigned int            mWidth;
    float                   mFOV;
    Scene::Camera           mInitialCamera;
    std::string             mTitle;
    std::shared_ptr<Scene>  mScene;
    std::string             mSceneFile;

public:
    SceneHandle(const std::string &title);
    void setInitialCamera(const Scene::Camera &camera);
    void setFOV(float fov);
    void setSize(const unsigned int width, const unsigned int height);
    void setScene(std::shared_ptr<Scene> scene);
    void setSceneFile(const std::string &scenefile);
    void loadScene(const std::string &scene);
    void run(int &argc, char** argv);
private:
};







#endif
