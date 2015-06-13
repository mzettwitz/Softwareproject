#include "../include/display.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_namespace.h>
//#include "../include/antTBar.h"

using namespace optix;

SimpleScene*        Display::mScene = 0;
std::string         Display::mTitle = "";
int                 Display::mWidth = 800;
int                 Display::mHeight = 800;
float               Display::horizontalAngle = 0.0f;
float               Display::verticalAngle = 0.0f;
float               Display::initialFOV = 45.f;
float               Display::mouseSpeed = 0.002f;
float3              Display::cameraPosition = make_float3(7,3,7);
float3              Display::cameraDirection = make_float3(0,0,0);
float3              Display::cameraRight = make_float3(0,0,1);
float3              Display::cameraUp = make_float3(0,0,0);
int                 Display::oldx = 0;
int                 Display::oldy = 0;
float                 Display::deltaTime = 0.0f;
int                 Display::mState = Display::mouseState::IDLE;
float ttime = 1.f;
void Display::init(int &argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(mWidth,mHeight);

    // AntTweakBar
    // redirecte GLUT events to ATB
    glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
    glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT); // same as MouseMotion
    glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
    glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);


    // send the "glutGetModifers" function pointer to ATB
    TwGLUTModifiersFunc(glutGetModifiers);

    //hardcoded
    int test = 0;
    //TwBar *bar;

    // Init ATB
<<<<<<< HEAD
    //TwWindowSize(mWidth, mHeight);
    //TwInit(TW_OPENGL, NULL);


    // Create ATB

   // bar = TwNewBar("MyBar");
    //TwDefine(" MyBar size='200 400' color='118 185 0' ");
=======
    TwInit(TW_OPENGL, NULL);


    // Create ATB
    bar = TwNewBar("MyBar");
    TwDefine(" MyBar size='200 400' color='118 185 0' ");
>>>>>>> 567047dde46d6853ac455a6cb2e7851d2176d6e7
    //TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLUT and OpenGL.' ");
   // TwAddVarRW(bar, "Test", TW_TYPE_INT32, &test, "");

}

void Display::run(const std::string &title, SimpleScene *scene)
{
    mScene = scene;
    mTitle = title;

    glutCreateWindow(title.c_str());

    float3 pos = make_float3(7,3,-3);
    float3 dir = make_float3(0,0,0);
    float3 rig = make_float3(0,0,1);
    SimpleScene::Camera c(pos,dir,rig);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    int buffer_width, buffer_height;
    try
    {
        mScene->initScene(c);
        Buffer buffer = mScene->getOutputBuffer();
        RTsize buffer_width_rts, buffer_height_rts;
        buffer->getSize(buffer_width_rts,buffer_height_rts);
        buffer_width = static_cast<int>(buffer_width_rts);
        buffer_height = static_cast<int>(buffer_height_rts);

    } catch (Exception e)
    {

        std::cout << "Failed to read buffer" << std::endl;
        exit(2);
    }


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1,0,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,buffer_width,buffer_height);


    glutShowWindow();
    glutReshapeWindow(buffer_width,buffer_height);

<<<<<<< HEAD
   // glutReshapeFunc(resize);
=======
    glutReshapeFunc(resize);
>>>>>>> 567047dde46d6853ac455a6cb2e7851d2176d6e7
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutMainLoop();

    //KILL ATB
   //TwTerminate();

}

void Display::display()
{
    int start = glutGet(GLUT_ELAPSED_TIME);
    SimpleScene::Camera c(cameraPosition,cameraDirection,cameraRight);

    std::cout << c.position.y << std::endl;
    mScene->trace(c);
    displayFrame();
    glutSwapBuffers();

    int end = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = float(end-start)/1000.0f;
}

void Display::displayFrame()
{
    Buffer buffer  = mScene->getOutputBuffer();
    RTsize bufferWidthRts, bufferHeightRts;
    buffer->getSize(bufferWidthRts,bufferHeightRts);
    int bufferWidth = static_cast<int>(bufferWidthRts);
    int bufferHeight = static_cast<int>(bufferHeightRts);
    RTformat bufferFormat = buffer->getFormat();

    GLvoid* imageData = buffer->map();

    GLenum glDataType = GL_FALSE;
    GLenum glFormat = GL_FALSE;

    switch(bufferFormat)
    {
    case RT_FORMAT_UNSIGNED_BYTE4 :
        glDataType = GL_UNSIGNED_BYTE;
        glFormat = GL_BGRA;
        break;
    case RT_FORMAT_FLOAT :
        glDataType = GL_FLOAT;
        glFormat = GL_LUMINANCE;
        break;
    case RT_FORMAT_FLOAT3 :
        glDataType = GL_FLOAT;
        glDataType = GL_RGB;
        break;
    case RT_FORMAT_FLOAT4 :
        glDataType = GL_FLOAT;
        glFormat = GL_RGBA;
        break;
    default :
        std::cout  <<"Unrecognized buffer data type or format.\n" << std::endl;
        exit(2);
        break;
    }

    RTsize elementSize = buffer->getElementSize();
    int align = 1;

    if((elementSize % 8) == 0)
        align = 8;
    else if((elementSize % 4) == 0)
        align = 4;
    else if((elementSize % 2) == 0)
        align = 2;

    glPixelStorei(GL_UNPACK_ALIGNMENT,align);
    glDrawPixels(static_cast<GLsizei>(bufferWidth),static_cast<GLsizei>(bufferHeight),glFormat,glDataType,imageData);
    buffer->unmap();

    //DRAW ATB
   // TwDraw();

<<<<<<< HEAD
   /* glBegin(GL_TRIANGLES);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(0,1,0);
    glEnd();*/
=======

>>>>>>> 567047dde46d6853ac455a6cb2e7851d2176d6e7

    glutPostRedisplay();
}

void Display::resize(int width, int height)
{

    // Send the new window size to AntTweakBar
    TwWindowSize(width, height);
}

void Display::keyPressed(unsigned char key, int x, int y)
{

    if(key == 119)
    {
        cameraPosition += make_float3(0.0f,0.02f,0.0f);
    }
    if(key == 49)
    {
        cameraPosition += 0.02f * cameraDirection;
    }
    if(key == 50)
        cameraPosition += 0.02f * cameraRight;
    if(key == 51)
    {
        cameraPosition -= 0.02f * cameraRight;
    }
    if(key == 52)
    {
        cameraPosition -= 0.02f * cameraDirection;
    }
    glutPostRedisplay();
}

void Display::mouseButton(int button, int state, int x, int y)
{

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        Display::mState = mouseState::MOVE;
    }
    else
    {
        state = mouseState::IDLE;
    }

}

void Display::mouseMotion(int x, int y)
{
    int deltaX = x - oldx;
    int deltaY = y - oldy;
   // if(mState ==  mouseState::MOVE)
    //{
    horizontalAngle += mouseSpeed *  deltaTime * float(mWidth/2 - x);
    verticalAngle += mouseSpeed * deltaTime * float(mHeight/2 - y);

    cameraDirection = make_float3(cos(verticalAngle) * sin(horizontalAngle),sin(verticalAngle),cos(verticalAngle) * cos(horizontalAngle));
    cameraRight = make_float3(sin(horizontalAngle - 3.14f/2.0f),0,cos(horizontalAngle - 3.14f/2.0f));

  //  }
    oldx = x;
    oldy = y;
    glutPostRedisplay();
}

