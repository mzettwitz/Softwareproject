#include "../sopro/include/ATB/antTBar.h"


// Baisc method to initialize all given variables
void antTBar(std::shared_ptr<Scene> scene, TwBar *matBar, TwBar *geomBar)
{
    antTBar_material(scene, matBar);
    antTBar_geometry(scene, geomBar);
}

