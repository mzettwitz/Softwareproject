#include "../sopro/include/ATB/antTBar.h"
#include "../sopro/include/ATB/antTBar_geometry.h"


//--------------------------------- Callback Functions
//----- Position getter X
static void TW_CALL getPositionXCB(void* value, void* clientData)
{
    // get sceneObject
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    // get position from object
    *((float*) value) = tmpO->position().x;
}
//----- Position setter X
static void TW_CALL setPositionXCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    float v = *((float*)value);
    // create a new Geometry
    tmpO->setPosition(v, 0);
}
//----- Position getter Y
static void TW_CALL getPositionYCB(void* value, void* clientData)
{
    // get sceneObject
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    // get position from object
    *((float*) value) = tmpO->position().y;
}
//----- Position setter Y
static void TW_CALL setPositionYCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    float v = *((float*)value);
    // create a new Geometry
    tmpO->setPosition(v, 1);

}
//----- Position getter Z
static void TW_CALL getPositionZCB(void* value, void* clientData)
{
    // get sceneObject
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    // get position from object
    *((float*) value) = tmpO->position().z;
}
//----- Position setter Z
static void TW_CALL setPositionZCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    float v = *((float*)value);
    // create a new Geometry
    tmpO->setPosition(v, 2);
}

//----- Rotation getter
static void TW_CALL getRotationCB(void* value, void* clientData)
{
    // get sceneObject
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    // get position from object
    *((float3*) value) = tmpO->rotation();
}
//----- Rotation getter
static void TW_CALL setRotationCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    float3 v = *((float3*)value);
    // create a new Geometry
    tmpO->setRotation(v);
}

//----- Scale getter
static void TW_CALL getScale3CB(void* value, void* clientData)
{
    // get sceneObject
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    // get position from object
    *((float*) value) = (tmpO->scale().x + tmpO->scale().y + tmpO->scale().z)/3.f;
}
//----- Scale setter
static void TW_CALL setScale3CB(const void* value, void* clientData)
{
    // save params in temporary pointer
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    float v = *((float*)value);
    // create a new Geometry
    tmpO->setScale(v,0);
    tmpO->setScale(v,1);
    tmpO->setScale(v,2);
}
//----- Scale getter X
static void TW_CALL getScaleXCB(void* value, void* clientData)
{
    // get sceneObject
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    // get position from object
    *((float*) value) = tmpO->scale().x;
}
//----- Scale setter X
static void TW_CALL setScaleXCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    float v = *((float*)value);
    // create a new Geometry
    tmpO->setScale(v, 0);
}
//----- Scale getter Y
static void TW_CALL getScaleYCB(void* value, void* clientData)
{
    // get sceneObject
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    // get position from object
    *((float*) value) = tmpO->scale().y;
}
//----- Scale setter Y
static void TW_CALL setScaleYCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    float v = *((float*)value);
    // create a new Geometry
    tmpO->setScale(v, 1);
}
//----- Scale getter Z
static void TW_CALL getScaleZCB(void* value, void* clientData)
{
    // get sceneObject
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    // get position from object
    *((float*) value) = tmpO->scale().z;
}
//----- Scale setter Z
static void TW_CALL setScaleZCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    BaseGeometry* tmpO =  static_cast<BaseGeometry*>(clientData);
    float v = *((float*)value);
    // create a new Geometry
    tmpO->setScale(v, 2);
}

//----- AreaPlane Dimensions X getter
static void TW_CALL getAreaDimensionsXCB(void* value, void* clientData)
{
    AreaPlane* tmpO =  static_cast<AreaPlane*>(clientData);
    *((float*) value) =  tmpO->dimensionsX();
}
//----- AreaPlane Dimensions X setter
static void TW_CALL setAreaDimensionsXCB(const void* value, void* clientData)
{
    AreaPlane* tmpO =  static_cast<AreaPlane*>(clientData);
    float v = *((float*)value);
    tmpO->setDimensionsX(v);
}

//----- AreaPlane Dimensions Y getter
static void TW_CALL getAreaDimensionsYCB(void* value, void* clientData)
{
    AreaPlane* tmpO =  static_cast<AreaPlane*>(clientData);
    *((float*) value) =  tmpO->dimensionsY();
}
//----- AreaPlane Dimensions Y setter
static void TW_CALL setAreaDimensionsYCB(const void* value, void* clientData)
{
    AreaPlane* tmpO =  static_cast<AreaPlane*>(clientData);
    float v = *((float*)value);
    tmpO->setDimensionsY(v);
}

//----- InfPlane Height getter
static void TW_CALL getInfHeightCB(void* value, void* clientData)
{
    InfinitePlane* tmpO =  static_cast<InfinitePlane*>(clientData);
    *((float*) value) =  tmpO->height();
}
//----- InfPlane Height setter
static void TW_CALL setInfHeightCB(const void* value, void* clientData)
{
    InfinitePlane* tmpO =  static_cast<InfinitePlane*>(clientData);
    float v = *((float*)value);
    tmpO->setHeight(v);
}

//----- Sphere Scale getter
static void TW_CALL getSphereRadiusCB(void* value, void* clientData)
{
    Sphere* tmpO =  static_cast<Sphere*>(clientData);
    *((float*) value) =  tmpO->scale().x;
}
//----- Sphere Scale setter
static void TW_CALL setSphereRadiusCB(const void* value, void* clientData)
{
    Sphere* tmpO =  static_cast<Sphere*>(clientData);
    float v = *((float*)value);
    tmpO->setScale(make_float3(v,v,v));
}

//--------------------------------- Basic variable init
void antTBar_geometry(std::shared_ptr<Scene> scene, TwBar *bar)
{
    for(int i = 0; i < scene->getSceneObjectCount(); i++)
    {
        antTBarInit_geometry(scene->getSceneObject(i).get(), bar, scene->getSceneObject(i)->getName());
    }
}

//--------------------------------- Variable init
void antTBarInit_geometry(SceneObject* scObj, TwBar *bar, std::string objName)
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

    // (,)
    std::string grpNameFloat = grpName + " step=0.05 ";
    const char* grpNameFloatC = grpNameFloat.c_str();

    //----------------- Geometry is AreaPlane
    if(scObj->getGeometry()->getGeometryType() == BaseGeometry::AREAPLANE){
        //---------- set name to specific variable
        std::string nameVar1 = name + " X-Position";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = name + " Y-Position";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = name + " Z-Position";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = name + " X-Dimension";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = name + " Y-Dimension";
        const char* nameVar5C = nameVar5.c_str();

        //---------- ATB variables
        // ATB Variable to set position and dimensions
        TwAddVarCB(bar, nameVar1C, TW_TYPE_FLOAT, setPositionXCB, getPositionXCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPositionYCB, getPositionYCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPositionZCB, getPositionZCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setAreaDimensionsXCB, getAreaDimensionsXCB, scObj->getGeometry().get(), grpNameFloat0C);
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setAreaDimensionsYCB, getAreaDimensionsYCB, scObj->getGeometry().get(), grpNameFloat0C);

        //---------- ATB subgroups
        // define strings for subgroups
        std::string positionGroup;
        positionGroup += " GeomBar/'" + nameVar1 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + nameVar2 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + nameVar3 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + objName + " Position' opened=false     \n";
        positionGroup += " GeomBar/' " + objName + "' opened=false     \n";
        positionGroup += " GeomBar/'" + objName + " Position'  group=' " + objName + "'  ";
        const char* positionGroupC = positionGroup.c_str();

        std::string propertyGroup;
        propertyGroup += " GeomBar/'" + nameVar4 + "'   group='" + objName + " Properties'     \n";
        propertyGroup += " GeomBar/'" + nameVar5 + "'   group='" + objName + " Properties'     \n";
        propertyGroup += " GeomBar/'" + objName + " Properties' opened=false     \n";
        propertyGroup += " GeomBar/'" + objName + " Properties'  group=' " + objName + "'  ";
        const char* propertyGroupC = propertyGroup.c_str();

        // define subgroups in ATB
        TwDefine(positionGroupC);
        TwDefine(propertyGroupC);

    }
    //---------------- Geometry is InfinitePlane
    else if(scObj->getGeometry()->getGeometryType() == BaseGeometry::INFINITEPLANE)
    {
        //---------- set name to specific variable
        std::string nameVar1 = name + " Height";
        const char* nameVar1C = nameVar1.c_str();

        //------------ ATB variables
        // ATB Variable to set height
        TwAddVarCB(bar, nameVar1C, TW_TYPE_FLOAT, setInfHeightCB, getInfHeightCB, scObj->getGeometry().get(), grpNameFloatC);

    }
    //---------------- Geometry is Sphere
    else if(scObj->getGeometry()->getGeometryType() == BaseGeometry::SPHERE)
    {
        //---------- set name to specific variable
        std::string nameVar1 = name + " X-Position";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = name + " Y-Position";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = name + " Z-Position";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = name + " Rotation";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = name + " Scale3";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = name + " Scale X";
        const char* nameVar6C = nameVar6.c_str();

        std::string nameVar7 = name + " Scale Y";
        const char* nameVar7C = nameVar7.c_str();

        std::string nameVar8 = name + " Scale Z";
        const char* nameVar8C = nameVar8.c_str();

        //------------ ATB variables
        // ATB Variable for position
        TwAddVarCB(bar, nameVar1C, TW_TYPE_FLOAT, setPositionXCB, getPositionXCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPositionYCB, getPositionYCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPositionZCB, getPositionZCB, scObj->getGeometry().get(), grpNameFloatC);

        // ATB Variable for Rotation
        TwAddVarCB(bar, nameVar4C, TW_TYPE_DIR3F, setRotationCB, getRotationCB, scObj->getGeometry().get(), grpNameC);

        // ATB Variable for Scale
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setScale3CB, getScale3CB, scObj->getGeometry().get(), grpNameFloat0C);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setScaleXCB, getScaleXCB, scObj->getGeometry().get(), grpNameFloat0C);
        TwAddVarCB(bar, nameVar7C, TW_TYPE_FLOAT, setScaleYCB, getScaleYCB, scObj->getGeometry().get(), grpNameFloat0C);
        TwAddVarCB(bar, nameVar8C, TW_TYPE_FLOAT, setScaleZCB, getScaleZCB, scObj->getGeometry().get(), grpNameFloat0C);

        //---------- ATB subgroups
        // define strings for subgroups
        std::string positionGroup;
        positionGroup += " GeomBar/'" + nameVar1 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + nameVar2 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + nameVar3 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + objName + " Position' opened=false     \n";
        positionGroup += " GeomBar/' " + objName + "' opened=false     \n";
        positionGroup += " GeomBar/'" + objName + " Position'  group=' " + objName + "'  ";
        const char* positionGroupC = positionGroup.c_str();

        std::string scaleGroup;
        scaleGroup += " GeomBar/'" + nameVar5 + "'   group='" + objName + " Scale'     \n";
        scaleGroup += " GeomBar/'" + nameVar6 + "'   group='" + objName + " Scale'     \n";
        scaleGroup += " GeomBar/'" + nameVar7 + "'   group='" + objName + " Scale'     \n";
        scaleGroup += " GeomBar/'" + nameVar8 + "'   group='" + objName + " Scale'     \n";
        scaleGroup += " GeomBar/'" + objName + " Scale' opened=false     \n";
        scaleGroup += " GeomBar/'" + objName + " Scale'  group=' " + objName + "'  ";
        const char* scaleGroupC = scaleGroup.c_str();

        // define subgroups in ATB
        TwDefine(positionGroupC);
        TwDefine(scaleGroupC);
    }
    //---------------- Geometry is Mesh
    else if(scObj->getGeometry()->getGeometryType() == BaseGeometry::MESH)
    {
        //---------- set name to specific variable
        std::string nameVar1 = name + " X-Position";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = name + " Y-Position";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = name + " Z-Position";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = name + " Rotation";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = name + " Scale3";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = name + " Scale X";
        const char* nameVar6C = nameVar6.c_str();

        std::string nameVar7 = name + " Scale Y";
        const char* nameVar7C = nameVar7.c_str();

        std::string nameVar8 = name + " Scale Z";
        const char* nameVar8C = nameVar8.c_str();

        //------------ ATB variables
        // ATB Variable for position
        TwAddVarCB(bar, nameVar1C, TW_TYPE_FLOAT, setPositionXCB, getPositionXCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPositionYCB, getPositionYCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPositionZCB, getPositionZCB, scObj->getGeometry().get(), grpNameFloatC);

        // ATB Variable for Rotation
        TwAddVarCB(bar, nameVar4C, TW_TYPE_DIR3F, setRotationCB, getRotationCB, scObj->getGeometry().get(), grpNameC);

        // ATB Variable for Scale
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setScale3CB, getScale3CB, scObj->getGeometry().get(), grpNameFloat0C);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setScaleXCB, getScaleXCB, scObj->getGeometry().get(), grpNameFloat0C);
        TwAddVarCB(bar, nameVar7C, TW_TYPE_FLOAT, setScaleYCB, getScaleYCB, scObj->getGeometry().get(), grpNameFloat0C);
        TwAddVarCB(bar, nameVar8C, TW_TYPE_FLOAT, setScaleZCB, getScaleZCB, scObj->getGeometry().get(), grpNameFloat0C);

        //---------- ATB subgroups
        // define strings for subgroups
        std::string positionGroup;
        positionGroup += " GeomBar/'" + nameVar1 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + nameVar2 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + nameVar3 + "'   group='" + objName + " Position'     \n";
        positionGroup += " GeomBar/'" + objName + " Position' opened=false     \n";
        positionGroup += " GeomBar/' " + objName + "' opened=false     \n";
        positionGroup += " GeomBar/'" + objName + " Position'  group=' " + objName + "'  ";
        const char* positionGroupC = positionGroup.c_str();

        std::string scaleGroup;
        scaleGroup += " GeomBar/'" + nameVar5 + "'   group='" + objName + " Scale'     \n";
        scaleGroup += " GeomBar/'" + nameVar6 + "'   group='" + objName + " Scale'     \n";
        scaleGroup += " GeomBar/'" + nameVar7 + "'   group='" + objName + " Scale'     \n";
        scaleGroup += " GeomBar/'" + nameVar8 + "'   group='" + objName + " Scale'     \n";
        scaleGroup += " GeomBar/'" + objName + " Scale' opened=false     \n";
        scaleGroup += " GeomBar/'" + objName + " Scale'  group=' " + objName + "'  ";
        const char* scaleGroupC = scaleGroup.c_str();

        // define subgroups in ATB
        TwDefine(positionGroupC);
        TwDefine(scaleGroupC);
    }
}

//--------------------------------- Clear object specific variables
void antTBarRemoveVariable_geometry(SceneObject *scObj, TwBar *bar, std::string objName)
{
    //----------------- Geometry is AreaPlane
    if(scObj->getGeometry()->getGeometryType() == BaseGeometry::AREAPLANE){
        //---------- set name to specific variable
        std::string nameVar1 = objName + " X-Position";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = objName + " Y-Position";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = objName + " Z-Position";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = objName + " X-Dimension";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Y-Dimension";
        const char* nameVar5C = nameVar5.c_str();

        //---------- ATB variables
        // ATB Variables to set position and dimensions
        TwRemoveVar(bar, nameVar1C);
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);
        TwRemoveVar(bar, nameVar4C);
        TwRemoveVar(bar, nameVar5C);

    }
    //---------------- Geometry is InfinitePlane
    else if(scObj->getGeometry()->getGeometryType() == BaseGeometry::INFINITEPLANE)
    {
        //---------- set name to specific variable
        std::string nameVar1 = objName + " Height";
        const char* nameVar1C = nameVar1.c_str();

        //------------ ATB variables
        // ATB Variable to set height
        TwRemoveVar(bar, nameVar1C);

    }
    //---------------- Geometry is Sphere
    else if(scObj->getGeometry()->getGeometryType() == BaseGeometry::SPHERE)
    {
        //---------- set name to specific variable
        std::string nameVar1 = objName + " X-Position";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = objName + " Y-Position";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = objName + " Z-Position";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = objName + " Rotation";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Scale3";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = objName + " Scale X";
        const char* nameVar6C = nameVar6.c_str();

        std::string nameVar7 = objName + " Scale Y";
        const char* nameVar7C = nameVar7.c_str();

        std::string nameVar8 = objName + " Scale Z";
        const char* nameVar8C = nameVar8.c_str();

        //------------ ATB variables
        // ATB Variable for position and radius
        TwRemoveVar(bar, nameVar1C);
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);
        TwRemoveVar(bar, nameVar4C);
        TwRemoveVar(bar, nameVar5C);
        TwRemoveVar(bar, nameVar6C);
        TwRemoveVar(bar, nameVar7C);
        TwRemoveVar(bar, nameVar8C);
    }
    //---------------- Geometry is Mesh
    else if(scObj->getGeometry()->getGeometryType() == BaseGeometry::MESH)
    {
        //---------- set name to specific variable
        std::string nameVar1 = objName + " X-Position";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = objName + " Y-Position";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = objName + " Z-Position";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = objName + " Rotation";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Scale3";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = objName + " Scale X";
        const char* nameVar6C = nameVar6.c_str();

        std::string nameVar7 = objName + " Scale Y";
        const char* nameVar7C = nameVar7.c_str();

        std::string nameVar8 = objName + " Scale Z";
        const char* nameVar8C = nameVar8.c_str();

        //------------ ATB variables
        // ATB Variable for position and radius
        TwRemoveVar(bar, nameVar1C);
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);
        TwRemoveVar(bar, nameVar4C);
        TwRemoveVar(bar, nameVar5C);
        TwRemoveVar(bar, nameVar6C);
        TwRemoveVar(bar, nameVar7C);
        TwRemoveVar(bar, nameVar8C);
    }
}
