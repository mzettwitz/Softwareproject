#include "../include/program3.h"
#include "../include/sceneHandle.h"
#include <optixu/optixpp_namespace.h>
#include "../include/display.h"

using namespace optix;

int program3(int argc, char* argv[])
{
   /*SceneHandle shp3("Program 3");

    shp3.setSceneFile("testscene.ssf");

    shp3.setFOV(45.0f);
    shp3.setSize(1024,1024);
    float3 position = make_float3(7,3,-20);
    float3 direction = make_float3(0,0,1);
    float3 right = make_float3(-1,0,0);
    shp3.setInitialCamera(Scene::Camera(position,direction,right));
    shp3.run(argc,argv);*/

   Display::init(argc,argv,"testscene.ssf");
   Display::run("cornellBox",nullptr);

    return 0;
}
