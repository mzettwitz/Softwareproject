#include "../sopro/include/ATB/antTBar.h"
#include "../sopro/include/ATB/antTBar_light.h"

//--------------------------------- Callback Functions
//----- Position getter X
static void TW_CALL getPositionXCB(void* value, void* clientData)
{
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    *((float*) value) = tmpO->positionIdx(0);
}
//----- Position setter X
static void TW_CALL setPositionXCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    float v = *((float*)value);
    tmpO->setPositionIdx(v, 0);
}
//----- Position getter Y
static void TW_CALL getPositionYCB(void* value, void* clientData)
{
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    *((float*) value) = tmpO->positionIdx(1);
}
//----- Position setter Y
static void TW_CALL setPositionYCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    float v = *((float*)value);
    tmpO->setPositionIdx(v, 1);
}
//----- Position getter Z
static void TW_CALL getPositionZCB(void* value, void* clientData)
{
    // get sceneObject
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    *((float*) value) = tmpO->positionIdx(2);
}
//----- Position setter Z
static void TW_CALL setPositionZCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    float v = *((float*)value);
    tmpO->setPositionIdx(v, 2);
}

//----- Color getter
static void TW_CALL getColorCB(void* value, void* clientData)
{
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    *((float3*) value) = tmpO->color();
}
//----- Color setter
static void TW_CALL setColorCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    float3 v = *((float3*)value);
    tmpO->setColor(v);
}

//----- Intensity getter
static void TW_CALL getIntensityCB(void* value, void* clientData)
{
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    *((float*) value) = tmpO->intensity();
}
//----- Intensity setter
static void TW_CALL setIntensityCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    PointLightClass* tmpO =  static_cast<PointLightClass*>(clientData);
    float v = *((float*)value);
    tmpO->setIntensity(v);
}


//--------------------------------- Basic variable init
void antTBar_light(std::shared_ptr<Scene> scene, TwBar *bar)
{
    for(int i = 0; i < scene->getLightCount(); i++)
    {
        antTBarInit_light(scene->getClassLight(i), bar, scene->getClassLight(i)->name());
    }
}

//--------------------------------- Variable init
void antTBarInit_light(std::shared_ptr<PointLightClass> light, TwBar *bar, std::string objName)
{
    //--------------- Generate names
    // object name
    std::string name = objName;

    //----- name for object group
    std::string grpName = " group=' ";
    grpName += name;
    grpName += "' ";
    const char* grpNameC = grpName.c_str();

    //-----name for object group + float steps extension
    // [0,)
    std::string grpNameFloat0 = grpName + " min=0 step=0.05 ";
    const char* grpNameFloat0C = grpNameFloat0.c_str();

    // [0,)
    std::string grpNameFloat0L = grpName + " min=0 step=10 ";
    const char* grpNameFloat0LC = grpNameFloat0L.c_str();

    // (,)
    std::string grpNameFloat = grpName + " step=0.05 ";
    const char* grpNameFloatC = grpNameFloat.c_str();

    //---------- set name to specific variable
    std::string nameVar1 = name + " Color";
    const char* nameVar1C = nameVar1.c_str();

    std::string nameVar2 = name + " X-Position";
    const char* nameVar2C = nameVar2.c_str();

    std::string nameVar3 = name + " Y-Position";
    const char* nameVar3C = nameVar3.c_str();

    std::string nameVar4 = name + " Z-Position";;
    const char* nameVar4C = nameVar4.c_str();

    std::string nameVar5 = name + " Intensity";
    const char* nameVar5C = nameVar5.c_str();

    //---------- ATB variables
    // ATB Variable to set position and dimensions
    TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, light.get(), grpNameC);
    TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPositionXCB, getPositionXCB, light.get(), grpNameFloatC);
    TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPositionYCB, getPositionYCB, light.get(), grpNameFloatC);
    TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPositionZCB, getPositionZCB, light.get(), grpNameFloatC);
    TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setIntensityCB, getIntensityCB, light.get(), grpNameFloat0LC);

    //---------- ATB subgroups
    // define strings for subgroups
    std::string propertyGroup;
    propertyGroup += " LightBar/'" + nameVar2 + "'   group='" + name + " Properties'     \n";
    propertyGroup += " LightBar/'" + nameVar3 + "'   group='" + name + " Properties'     \n";
    propertyGroup += " LightBar/'" + nameVar4 + "'   group='" + name + " Properties'     \n";
    propertyGroup += " LightBar/'" + nameVar5 + "'   group='" + name + " Properties'     \n";
    propertyGroup += " LightBar/'" + name + " Properties' opened=false     \n";
    propertyGroup += " LightBar/' " + name + "' opened=false     \n";
    propertyGroup += " LightBar/'" + name + " Properties'  group=' " + name + "'  ";
    const char* propertyGroupC = propertyGroup.c_str();

    // define subgroups in ATB
    TwDefine(propertyGroupC);
}

//--------------------------------- Clear object specific variables
void antTBarRemoveVariable_light(TwBar *bar, std::string objName)
{
    //---------- set name to specific variable
    std::string nameVar1 = objName + " Color";
    const char* nameVar1C = nameVar1.c_str();

    std::string nameVar2 = objName + " X-Position";
    const char* nameVar2C = nameVar2.c_str();

    std::string nameVar3 = objName + " Y-Position";
    const char* nameVar3C = nameVar3.c_str();

    std::string nameVar4 = objName + " Z-Position";;
    const char* nameVar4C = nameVar4.c_str();

    std::string nameVar5 = objName + " Intensity";
    const char* nameVar5C = nameVar5.c_str();

    //---------- ATB variables
    // ATB Variables to set position and dimensions
    TwRemoveVar(bar, nameVar1C);
    TwRemoveVar(bar, nameVar2C);
    TwRemoveVar(bar, nameVar3C);
    TwRemoveVar(bar, nameVar4C);
    TwRemoveVar(bar, nameVar5C);



}
