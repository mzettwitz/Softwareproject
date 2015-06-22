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
    static int                  mWidth, mHeight;
    static float                horizontalAngle;
    static float                verticalAngle;
    static float                initialFOV;
    static float                mouseSpeed;
    static float3               cameraPosition;
    static float3               cameraDirection;
    static float3               cameraRight;
    static float3               cameraUp;
    static int                  oldx;
    static int                  oldy;
    static float                deltaTime;
    static int                  mState;

    enum mouseState
    {
       ROTATE = 1,
       MOVE = 2,
       IDLE = 3

    };

public:
    static void                 init(int &argc, char** argv);
    static void                 run(const std::string &title, std::shared_ptr<Scene> scene);

private:
    static void                 displayFrame();
    static void                 quit();
    static void                 display();
    static void                 keyPressed(unsigned char key, int x,int y);
    static void                 mouseButton(int button, int mState, int x, int y);
    static void                 mouseMotion(int x, int y);
    static void                 resize(int width, int height);


};

#endif //DISPLAY_H
