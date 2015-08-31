#include "../sopro/include/ATB/antTBar.h"
#include "../sopro/include/ATB/antTBar_material.h"
#include "../sopro/include/ATB/antTBar_geometry.h"

// Baisc method to initialize all given variables
void antTBar(std::shared_ptr<Scene> scene, TwBar *matBar, TwBar *geomBar)
{
    antTBar_material(scene, matBar);
    antTBar_geometry(scene, geomBar);
}

