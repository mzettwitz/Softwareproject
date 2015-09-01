/*! \brief Geometry interface for AntTweakBar GUI
 *
 * Basic usage to setup geometry properties in a comfortable GUI
 *
 * \sa http://anttweakbar.sourceforge.net/doc/
 *
 */

#pragma once

#include "../AntTweakBar/include/AntTweakBar.h"
#include "../sopro/include/geometry/baseGeometry.h"
#include "../sopro/include/geometry/basePlane.h"
#include "../sopro/include/geometry/areaPlane.h"
#include "../sopro/include/geometry/infinitePlane.h"
#include "../sopro/include/geometry/sphere.h"
#include "../sopro/include/geometry/mesh.h"
#include "../sopro/include/scene.h"
#include <memory>
#include <iostream>

void antTBar_geometry(std::shared_ptr<Scene> scene, TwBar *bar);
void antTBarInit_geometry(SceneObject* scObj, TwBar *bar, std::string objName);
void antTBarRemoveVariable_geometry(SceneObject* scObj, TwBar *bar, std::string objName);

