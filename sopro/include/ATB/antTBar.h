/*! \brief Setup for AntTweakBar GUI
 *
 * Inintalizes AntTweakBar for editorial purposes in our scene.
 * Basic usage to setup material, position and light properties in a comfortable GUI
 *
 * \sa http://anttweakbar.sourceforge.net/doc/
 *
 */

#pragma once

#include "../AntTweakBar/include/AntTweakBar.h"
#include "../ATB/antTBar_material.h"
#include "../ATB/antTBar_geometry.h"
#include "../ATB/antTBar_light.h"
#include "../sopro/include/scene.h"
#include <memory>
#include <iostream>


void antTBar(std::shared_ptr<Scene> scene, TwBar *matBar, TwBar *geomBar, TwBar *lightBar);





