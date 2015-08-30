#include "../sopro/include/ATB/antTBar.h"
#include "../sopro/include/ATB/antTBar_material.h"


// Baisc method to initialize all given variables
void antTBar(std::shared_ptr<Scene> scene, TwBar *matBar)
{
    antTBar_material(scene, matBar);
}

