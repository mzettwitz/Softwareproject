#include "../include/program3.h"
#include "../include/sceneHandle.h"
#include <optixu/optixpp_namespace.h>

using namespace optix;

int program3(int argc, char* argv[])
{

    SceneHandle shp3("Program 3");
    shp3.setFOV(45.0f);
    shp3.setSize(800,600);
    float3 position = make_float3(7,3,-20);
    float3 direction = make_float3(0,-1,0);
    float3 right = make_float3(0,0,1);
    shp3.setInitialCamera(Scene::Camera(position,direction,right));

    shp3.run(argc,argv);
    return 0;
}
