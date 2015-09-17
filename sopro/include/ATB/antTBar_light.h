/*! \brief Geometry interface for AntTweakBar GUI
 *
 * Basic usage to setup light properties in a comfortable GUI
 *
 * \sa http://anttweakbar.sourceforge.net/doc/
 *
 */

#pragma once

#include "../AntTweakBar/include/AntTweakBar.h"
#include "../sopro/include/pointlight.h"
#include "../sopro/include/scene.h"
#include <memory>
#include <iostream>


void antTBar_light(std::shared_ptr<Scene> scene, TwBar *bar);
void antTBarInit_light(std::shared_ptr<PointLightClass> light, TwBar *bar, std::string objName);
void antTBarRemoveVariable_light(TwBar *bar, std::string objName);


