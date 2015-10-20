#ifndef DISPLAY_H
#define DISPLAY_H

#include "scene.h"
#include <string>
#include <memory>

class Display
{
private:
    static std::shared_ptr<Scene> mScene;
    static std::string          mTitle;
    static std::string          mSource;
    static int                  mWidth, mHeight;
    static float                horizontalAngle;
    static float                verticalAngle;
    static float                initialFOV;
    static float                mouseSpeed;
    static float                moveSpeed;
    static float3               cameraPosition;
    static float3               cameraDirection;
    static float3               cameraRight;
    static bool                 cameraChanged;
    static int                  oldx;
    static int                  oldy;
    static float                deltaTime;
    static int                  mState;
    static bool                 loaded;
    static bool                 locked;

    enum mouseState
    {
       ROTATE = 1,
       MOVE = 2,
       IDLE = 3,
       ZOOM = 4
    };

public:
    static void                 init(int &argc, char** argv,const unsigned int width,const unsigned int height);
    static void                 init(int &argc, char** argv, const std::string &scenename);
    static void                 run(const std::string &title, std::shared_ptr<Scene> scene);
    static void                 setInitialCamera(const Scene::Camera &camera);
    static void                 setFOV(float fov);
    static void                 setSceneSource(const std::string &src);

private:
    static void                 displayFrame();
    static void                 quit();
    static void                 display();
    static void                 keyPressed(unsigned char key, int x,int y);
    static void                 mouseButton(int button, int mState, int x, int y);
    static void                 mouseMotion(int x, int y);
    static void                 resize(int width, int height);
    static void                 moveX(float speed);
    static void                 moveY(float speed);
    static void                 moveZ(float speed);


};

#endif //DISPLAY_H
