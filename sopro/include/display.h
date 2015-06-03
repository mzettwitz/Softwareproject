#ifndef DISPLAY_H
#define DISPLAY_H

#include "simpleScene.h"
#include <string>

class Display
{
public:
    static void init(int &argc, char** argv);
    static void run(const std::string &title, SimpleScene *scene);

private:
    static void displayFrame();
    static void quit();
    static void display();
    static void keyPressed(unsigned char key, int x,int y);
    static void mouseButton(int button, int state, int x, int y);
    static void mouseMotion(int x, int y);
    static void resize(int width, int height);


    static SimpleScene* mScene;
    static std::string mTitle;
    static int mWidth, mHeight;
 //   static int initialWidth, initialHeight = 500;
};




#endif //DISPLAY_H
