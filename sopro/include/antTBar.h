/*! \brief Setup for AntTweakBar GUI
 *
 * Inintalizes AntTweakBar for editorial purposes in our scene.
 * Basic usage to setup material properties in a comfortable GUI
 *
 * \sa http://anttweakbar.sourceforge.net/doc/
 *
 */

#pragma once

#include "../AntTweakBar/include/AntTweakBar.h"
#include "material/baseMaterial.h"
#include "material/lambertMaterial.h"
#include "material/phongMaterial.h"
#include "material/glassMaterial.h"
#include "material/disneyMaterial.h"
#include "scene.h"
#include <memory>
#include <iostream>



void antTBar(std::shared_ptr<Scene> scene, TwBar *bar);




