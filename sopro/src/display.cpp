#include "../include/display.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <optixu/optixpp_namespace.h>
#include <optixu/optixu_math_namespace.h>
#include "../sopro/include/ATB/antTBar.h"
#include "../include/geometry/sphere.h"
#include "../include/geometry/infinitePlane.h"
#include "../include/geometry/mesh.h"
#include "../include/geometry/meshgroup.h"
#include "../include/sceneLoader.h"


using namespace optix;

std::shared_ptr<Scene>        Display::mScene = 0;
std::string         Display::mTitle = "";
std::string         Display::mSource = "";
int                 Display::mWidth = 0;
int                 Display::mHeight = 0;
float               Display::horizontalAngle = 0.0f;
float               Display::verticalAngle = 0.0f;
float               Display::initialFOV = 0.0f;
float               Display::mouseSpeed = 0.002f;
float               Display::moveSpeed = 5.0f;
float3              Display::cameraPosition = make_float3(0,0,0);
float3              Display::cameraDirection = make_float3(0,0,0);
float3              Display::cameraRight = make_float3(0,0,0);
int                 Display::oldx = 0;
int                 Display::oldy = 0;
float               Display::deltaTime = 0.0f;
int                 Display::mState = Display::mouseState::IDLE;
bool                Display::cameraChanged = false;
bool                Display::loaded = false;
// Declare ATB
TwBar *matBar;
TwBar *geomBar;
TwBar *lightBar;

//dummy purpose
int                 count = 0;

void Display::init(int &argc, char **argv,const unsigned int width,const unsigned int height)
{
    mWidth = width;
    mHeight = height;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(mWidth,mHeight);

    // AntTweakBar
    //redirect GLUT events to ATB
    glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
    glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT); // same as MouseMotion
    glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
    glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);

    // send the "glutGetModifers" function pointer to ATB
    TwGLUTModifiersFunc(glutGetModifiers);

    // Init ATB
    TwInit(TW_OPENGL, NULL);

    // Create ATB
    matBar = TwNewBar("MatBar");
    TwDefine(" MatBar size='270 300' color='118 185 0' alpha=160 position='10 10'");

    geomBar = TwNewBar("GeomBar");
    TwDefine(" GeomBar size='270 300' color='118 185 0' alpha=160 position='10 320'");

    lightBar = TwNewBar("LightBar");
    TwDefine(" LightBar size='270 115' color='118 185 0' alpha=160 position='10 630'");
}

void Display::init(int &argc, char **argv, const std::string &scenename)
{
    mScene = std::make_shared<Scene>();
    std::vector<float> settings;
    SceneLoader::loadScene(scenename,mScene,settings);
    cameraPosition.x = settings.at(0);
    cameraPosition.y = settings.at(1);
    cameraPosition.z = settings.at(2);
    cameraDirection.x = settings.at(3);
    cameraDirection.y = settings.at(4);
    cameraDirection.z = settings.at(5);
    cameraRight.x = settings.at(6);
    cameraRight.y = settings.at(7);
    cameraRight.z = settings.at(8);
    horizontalAngle = settings.at(9);
    verticalAngle = settings.at(10);
    mWidth = settings.at(12);
    mHeight = settings.at(13);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(mWidth,mHeight);

    // AntTweakBar
    //redirect GLUT events to ATB
    glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
    glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT); // same as MouseMotion
    glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
    glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);

    // send the "glutGetModifers" function pointer to ATB
    TwGLUTModifiersFunc(glutGetModifiers);

    // Init ATB
    TwInit(TW_OPENGL, NULL);

    // Create ATB
    matBar = TwNewBar("MatBar");
    TwDefine(" MatBar size='270 300' color='118 185 0' alpha=160 position='10 10'");

    geomBar = TwNewBar("GeomBar");
    TwDefine(" GeomBar size='270 300' color='118 185 0' alpha=160 position='10 320'");

    lightBar = TwNewBar("LightBar");
    TwDefine(" LightBar size='270 115' color='118 185 0' alpha=160 position='10 630'");
}

void Display::run(const std::string &title, std::shared_ptr<Scene> scene)
{
    if(scene != nullptr)
    {
        mScene = scene;
    }
    mTitle = title;

    glutCreateWindow(title.c_str());

    cameraDirection = make_float3(cos(verticalAngle) * sin(horizontalAngle),sin(verticalAngle),cos(verticalAngle) * cos(horizontalAngle));
    cameraRight = make_float3(sin(horizontalAngle - 3.14f/2.0f),0,cos(horizontalAngle - 3.14f/2.0f));

    float3 pos = cameraPosition;
    float3 dir = cameraDirection;
    float3 rig = cameraRight;
    Scene::Camera c(pos,dir,rig);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    int buffer_width, buffer_height;
    try
    {
        mScene->initScene(c,mWidth,mHeight);
    } catch (Exception e)
    {
        std::cout << "Failed to initialize Scene" << std::endl;
        exit(2);
    }
    try
    {
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

    //GLUT functions
    glutReshapeFunc(resize);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);

    antTBar(mScene, matBar, geomBar, lightBar);

    glutMainLoop();

    //KILL ATB
    TwTerminate();

}

void Display::display()
{
    int start = glutGet(GLUT_ELAPSED_TIME);

    //for camera update
    Scene::Camera c(cameraPosition,cameraDirection,cameraRight);

    //call for optix trace
    mScene->passFrameNumber(cameraChanged);
    mScene->trace(c);

    //transfer optix buffer to opengl buffer
    displayFrame();

    glutSwapBuffers();

    int end = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = float(end-start)/1000.0f;
    std::cout << int(1.0f/deltaTime) << std::endl;
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

    TwDraw();   // draw ATB

    glutPostRedisplay();
}

void Display::resize(int width, int height)
{
    // Send the new window size to TweakBar
    mWidth = width;
    mHeight = height;
    TwWindowSize(width, height);
    mScene->resizeBuffer(width,height);
    glutPostRedisplay();
}

void Display::keyPressed(unsigned char key, int x, int y)
{
    // send event to ATB if not handled by ATB
    if(TwEventKeyboardGLUT(key, x, y))
    {}
    // send event to GLUT
    else
    {
        // w : upward
        if(key == 'w')
        {
            cameraPosition += moveSpeed * normalize(cross(cameraRight,cameraDirection)) * deltaTime * 0.25f;
        }
        // s : downward
        if(key == 's')
        {
            cameraPosition -= moveSpeed * normalize(cross(cameraRight,cameraDirection)) * deltaTime * 0.25f;
        }
        // a : left
        if(key == 'a')
        {
            cameraPosition -= moveSpeed * cameraRight * deltaTime * 0.25f;
        }
        // d : right
        if(key == 'd')
        {
            cameraPosition += moveSpeed * cameraRight * deltaTime * 0.25f;
        }
        // e : zoom in
        if(key == 'e')
        {
            cameraPosition += moveSpeed * cameraDirection * deltaTime * 0.25f;
        }
        // q : zoom out
        if(key == 'q')
        {
            cameraPosition -= moveSpeed * cameraDirection * deltaTime * 0.25f;
        }
        // + : dummy purpose, add dummy sphere
        if(key == '+')
        {

            std::shared_ptr<LambertMaterial> l = std::make_shared<LambertMaterial>(make_float3(0.3f,0.5f,0.9f));
            std::shared_ptr<Sphere> s = std::make_shared<Sphere>(make_float3(0.0f,0.0f,0.0f));
            std::string name = "Sphere_" + std::to_string(mScene->getSceneObjectCount());
            std::shared_ptr<SceneObject> obj = std::make_shared<SceneObject>(name,s,l);
            mScene->addSceneObject(obj);

            // add ATB variable
            // init new variables
            antTBarInit_material(obj.get(), matBar, name);
            antTBarInit_geometry(obj.get(), geomBar, name);

        }
        // - : dummy purpose, delete dummy sphere
        if(key == '-')
        {
            if(mScene->getSceneObjectCount() > 0)
            {
                // delete ATB variable
                antTBarRemoveVariable_material(mScene->getSceneObject(mScene->getSceneObjectCount()-1).get(),
                                               matBar, mScene->getSceneObject(mScene->getSceneObjectCount()-1)->getName());
                antTBarRemoveVariable_geometry(mScene->getSceneObject(mScene->getSceneObjectCount()-1).get(),
                                               geomBar, mScene->getSceneObject(mScene->getSceneObjectCount()-1)->getName());

                mScene->removeObject(mScene->getSceneObjectCount()-1);

            }
        }
        // y : set increase sceneEpsilon
        if(key == 'y')
        {
            mScene->setSceneEpsilon(-0.1e-3f);
        }
        // x : set decrease sceneEpsilon
        if(key == 'x')
        {
            mScene->setSceneEpsilon(0.1e-3f);
        }
        // 5 - load mesh group from assets directory and programm file
        if(key == '5')
        {
            std::shared_ptr<Mesh> m = std::make_shared<Mesh>("dragonBlender.obj",make_float3(0,0,0));
            m->load();
            std::shared_ptr<PhongMaterial> p = std::make_shared<PhongMaterial>(make_float3(1.0f,1.0f,1.0f),0.2f,0.6f,0.2f,5.2f,0.2f);
            std::string name = "Mesh_" + std::to_string(mScene->getSceneObjectCount());
            std::shared_ptr<SceneObject> sc = std::make_shared<SceneObject>(name,m,p);

            mScene->addSceneObject(sc);
            antTBarInit_material(sc.get(),matBar,name);
            antTBarInit_geometry(sc.get(),geomBar,name);
        }
        // load meshgroup as single mesh objects
        if(key == '6')
        {

            std::shared_ptr<MeshGroup> g = std::make_shared<MeshGroup>(mSource);
            g->load();
            std::shared_ptr<LambertMaterial> m = std::make_shared<LambertMaterial>(make_float3(1,1,1));
            for(unsigned int i = 0;i < g->data()->size();++i)
            {
                std::string name = g->data(i)->objectname();
                std::shared_ptr<SceneObject> sc = std::make_shared<SceneObject>(name,g->data(i),m);
                mScene->addSceneObject(sc);
                antTBarInit_material(sc.get(),matBar,name);
                antTBarInit_geometry(sc.get(),geomBar,name);
            }
        }

        //new groudPlane, just a box, but modified to a 'plane'
        if(key == '9')
        {
            std::shared_ptr<Mesh> groundPlane = std::make_shared<Mesh>("cube.obj",make_float3(0.0f,-2.0f,0.0f));
            groundPlane->load();
            groundPlane->setScale(make_float3(100.0f,0.2f,100.0f));
            std::shared_ptr<LambertMaterial> p = std::make_shared<LambertMaterial>(make_float3(1.0f,1.0f,1.0f));
            std::shared_ptr<SceneObject> sc = std::make_shared<SceneObject>("groundPlane",groundPlane,p);

            mScene->addSceneObject(sc);
            antTBarInit_material(sc.get(),matBar,"groundPlane");
            antTBarInit_geometry(sc.get(),geomBar,"groundPlane");
        }
        // add a pointlight
        if(key == 'l')
        {
            PointLight l;
            l.color = make_float3(1,1,1);
            l.intensity = 1000.0f;
            l.padding = 0;
            l.position = cameraPosition + 10 * cameraDirection;
            mScene->addLight(l);
            antTBarInit_light(mScene->getClassLight(mScene->getLightCount()-1),lightBar,mScene->getClassLight(mScene->getLightCount()-1)->name());
        }
        // a pointlight
        if(key == 'o')
        {
            antTBarRemoveVariable_light(lightBar,mScene->getClassLight(mScene->getLightCount()-1)->name());
            mScene->removeLight(mScene->getLightCount()-1);
        }
        // save scene
        if(key == 'b')
        {
            std::vector<float> settings;
            settings.push_back(cameraPosition.x);
            settings.push_back(cameraPosition.y);
            settings.push_back(cameraPosition.z);
            settings.push_back(cameraDirection.x);
            settings.push_back(cameraDirection.y);
            settings.push_back(cameraDirection.z);
            settings.push_back(cameraRight.x);
            settings.push_back(cameraRight.y);
            settings.push_back(cameraRight.z);
            settings.push_back(horizontalAngle);
            settings.push_back(verticalAngle);
            settings.push_back(45.0f);
            settings.push_back(static_cast<float>(mWidth));
            settings.push_back(static_cast<float>(mHeight));
            SceneLoader::saveScene("madScience",mScene,settings);
        }
        // load scene
        if(key == '1')
        {

            std::vector<float> settings;
            SceneLoader::loadScene(mSource,mScene,settings);
            cameraPosition.x = settings.at(0);
            cameraPosition.y = settings.at(1);
            cameraPosition.z = settings.at(2);
            cameraDirection.x = settings.at(3);
            cameraDirection.y = settings.at(4);
            cameraDirection.z = settings.at(5);
            cameraRight.x = settings.at(6);
            cameraRight.y = settings.at(7);
            cameraRight.z = settings.at(8);
            horizontalAngle = settings.at(9);
            verticalAngle = settings.at(10);
            mWidth = settings.at(12);
            mHeight = settings.at(13);

            for(unsigned int i = 0;i < mScene->getSceneObjectCount();++i)
            {
                antTBarInit_material(mScene->getSceneObject(i).get(),matBar,std::dynamic_pointer_cast<Mesh>(mScene->getSceneObject(i)->getGeometry())->objectname());
                antTBarInit_geometry(mScene->getSceneObject(i).get(),geomBar,std::dynamic_pointer_cast<Mesh>(mScene->getSceneObject(i)->getGeometry())->objectname());
            }
            for(unsigned int i = 0;i < mScene->getLightCount();++i)
            {
                antTBarInit_light(mScene->getClassLight(i),lightBar,mScene->getClassLight(i)->name());
            }
        }
    }
    cameraChanged = true;
    //needs to be called, to update change
    glutPostRedisplay();

}

void Display::mouseButton(int button, int state, int x, int y)
{
    // send event to AntTweakBar if not handled
    if( !TwEventMouseButtonGLUT( button, state, x, y) )
    {
        //left button pressed
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            TwMouseMotion(x, y);
            TwMouseButton(TW_MOUSE_PRESSED, TW_MOUSE_LEFT);
            Display::mState = mouseState::MOVE;
        }
        //left button released
        if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            TwMouseMotion(x, y);
            TwMouseButton(TW_MOUSE_RELEASED, TW_MOUSE_LEFT);
            Display::mState = mouseState::IDLE;
        }
    }

    // send event to GLUT
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            Display::mState = mouseState::MOVE;
        }
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            Display::mState = mouseState::ROTATE;
        }
    }
    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mState = mouseState::ZOOM;
        }
    }
}


void Display::mouseMotion(int x, int y)
{
    int deltaX, deltaY = 0;
    deltaX = x - oldx;
    deltaY = y - oldy;

    // using ATB bar?
    if( mState == mouseState::MOVE && TwEventMouseMotionGLUT( x, y))
    {

    }
    // else set camera
    else if(mState ==  mouseState::ROTATE)
    {

        horizontalAngle += mouseSpeed *  deltaTime * float(mWidth/2 - x) * 0.2f;
        verticalAngle += mouseSpeed * deltaTime * float(mHeight/2 - y) * 0.2f;

        cameraDirection = make_float3(cos(verticalAngle) * sin(horizontalAngle),sin(verticalAngle),cos(verticalAngle) * cos(horizontalAngle));
        cameraRight = make_float3(sin(horizontalAngle - 3.14f/2.0f),0,cos(horizontalAngle - 3.14f/2.0f));
    }
    else if (mState == mouseState::MOVE)
    {
        cameraPosition -= cameraRight * deltaTime * mouseSpeed * 5.0f * float(mWidth/2 - x);
        cameraPosition += cross(cameraRight,cameraDirection) * deltaTime * mouseSpeed * 5.0f * float(mHeight/2 - y);
    }
    else if(mState == mouseState::ZOOM)
    {
        cameraPosition += cameraDirection * deltaTime * mouseSpeed * 10.0f * float(mHeight/2 -y);
    }

    oldx = x;
    oldy = y;
    cameraChanged = true;

    glutPostRedisplay();
}

void Display::setInitialCamera(const Scene::Camera &camera)
{
    cameraPosition = camera.position;
    cameraDirection = camera.direction;
    cameraRight = camera.right;
}

void Display::setFOV(float fov)
{
    initialFOV = fov;
}

void Display::setSceneSource(const std::string &src)
{
    mSource = src;
}
