#include "../include/sceneHandle.h"
#include "../include/display.h"


SceneHandle::SceneHandle(const std::string &title) : mTitle(title),mHeight(600),mWidth(800),mFOV(45.0f),mScene(std::make_shared<Scene>())
{
    float3 pos = make_float3(0,0,0);
    float3 dir = make_float3(1,0,0);
    float3 rig = make_float3(0,0,1);
    mInitialCamera = Scene::Camera(pos,dir,rig);
}

void SceneHandle::setFOV(float fov)
{
    mFOV = fov;
}

void SceneHandle::setInitialCamera(const Scene::Camera &camera)
{
    mInitialCamera = camera;
}

void SceneHandle::setScene(std::shared_ptr<Scene> scene)
{
    mScene = scene;
}

void SceneHandle::setSize(const unsigned int width, const unsigned int height)
{
    mWidth = width;
    mHeight = height;
}


void SceneHandle::run(int &argc,char **argv)
{
    Display::init(argc,argv,mWidth,mHeight);
    Display::setFOV(mFOV);
    Display::setInitialCamera(mInitialCamera);
    Display::run(mTitle,mScene);
}
