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



void antTBar(int &width, int &height, std::vector<Material> &mat, Context &context);

//void TW_CALL setPhong(const void *value, void * /*clientData*/);
//void TW_CALL getPhong(void *value, void * /*clientData*/);

//void TW_CALL setDisney(const void *value, void * /*clientData*/);
//void TW_CALL getDisney(void *value, void * /*clientData*/);

float3 fTof3(float f[3]);


