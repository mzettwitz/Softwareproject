/*! \brief Material interface for AntTweakBar GUI
 *
 * Basic usage to setup material properties in a comfortable GUI
 *
 * \sa http://anttweakbar.sourceforge.net/doc/
 *
 */

#pragma once

#include "../AntTweakBar/include/AntTweakBar.h"
#include "../sopro/include/material/baseMaterial.h"
#include "../sopro/include/material/lambertMaterial.h"
#include "../sopro/include/material/phongMaterial.h"
#include "../sopro/include/material/glassMaterial.h"
#include "../sopro/include/material/disneyMaterial.h"
#include "../sopro/include/scene.h"
#include <memory>
#include <iostream>

void antTBar_material(std::shared_ptr<Scene> scene, TwBar *bar);
void antTBarReInit_material(std::string oldMat, SceneObject *scObj, TwBar *bar, std::string objName);
void antTBarInit_material(SceneObject* scObj, TwBar *bar, std::string objName);
void antTBarRemoveVariable_material(SceneObject* scObj, TwBar *bar, std::string objName);
