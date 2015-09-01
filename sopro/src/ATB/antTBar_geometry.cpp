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

//----- Sphere Radius getter
static void TW_CALL getSphereRadiusCB(void* value, void* clientData)
{
    Sphere* tmpO =  static_cast<Sphere*>(clientData);
    *((float*) value) =  tmpO->radius();
}
//----- Sphere Radius setter
static void TW_CALL setSphereRadiusCB(const void* value, void* clientData)
{
    Sphere* tmpO =  static_cast<Sphere*>(clientData);
    float v = *((float*)value);
    tmpO->setRadius(v);
}

//--------------------------------- Basic variable init
void antTBar_geometry(std::shared_ptr<Scene> scene, TwBar *bar)
{

    for(int i = 0; i < scene->getSceneObjectCount(); i++)
    {
        //--------------- Generate names
        // object name
        std::string name = scene->getSceneObject(i)->getName();

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
        if(scene->getSceneObject(i)->getGeometry()->getGeometryType() == BaseGeometry::AREAPLANE){
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
            TwAddVarCB(bar, nameVar1C, TW_TYPE_FLOAT, setPositionXCB, getPositionXCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPositionYCB, getPositionYCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPositionZCB, getPositionZCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setAreaDimensionsXCB, getAreaDimensionsXCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloat0C);
            TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setAreaDimensionsYCB, getAreaDimensionsYCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloat0C);

        }
        //---------------- Geometry is InfinitePlane
        else if(scene->getSceneObject(i)->getGeometry()->getGeometryType() == BaseGeometry::INFINITEPLANE)
        {
            //---------- set name to specific variable
            std::string nameVar1 = name + " Height";
            const char* nameVar1C = nameVar1.c_str();

            //------------ ATB variables
            // ATB Variable to set height
            TwAddVarCB(bar, nameVar1C, TW_TYPE_FLOAT, setInfHeightCB, getInfHeightCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloatC);

        }
        //---------------- Geometry is Sphere
        else if(scene->getSceneObject(i)->getGeometry()->getGeometryType() == BaseGeometry::SPHERE)
        {
            //---------- set name to specific variable
            std::string nameVar1 = name + " X-Position";
            const char* nameVar1C = nameVar1.c_str();

            std::string nameVar2 = name + " Y-Position";
            const char* nameVar2C = nameVar2.c_str();

            std::string nameVar3 = name + " Z-Position";
            const char* nameVar3C = nameVar3.c_str();

            std::string nameVar4 = name + " Radius";
            const char* nameVar4C = nameVar4.c_str();


            //------------ ATB variables
            // ATB Variable for position and radius
            TwAddVarCB(bar, nameVar1C, TW_TYPE_FLOAT, setPositionXCB, getPositionXCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPositionYCB, getPositionYCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPositionZCB, getPositionZCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setSphereRadiusCB, getSphereRadiusCB, scene->getSceneObject(i)->getGeometry().get(), grpNameFloat0C);
        }
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

        std::string nameVar4 = name + " Radius";
        const char* nameVar4C = nameVar4.c_str();


        //------------ ATB variables
        // ATB Variable for position and radius
        TwAddVarCB(bar, nameVar1C, TW_TYPE_FLOAT, setPositionXCB, getPositionXCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPositionYCB, getPositionYCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPositionZCB, getPositionZCB, scObj->getGeometry().get(), grpNameFloatC);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setSphereRadiusCB, getSphereRadiusCB, scObj->getGeometry().get(), grpNameFloat0C);
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

        std::string nameVar4 = objName + " Radius";
        const char* nameVar4C = nameVar4.c_str();


        //------------ ATB variables
        // ATB Variable for position and radius
        TwRemoveVar(bar, nameVar1C);
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);
        TwRemoveVar(bar, nameVar4C);
    }
}
