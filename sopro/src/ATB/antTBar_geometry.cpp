#include "../sopro/include/ATB/antTBar.h"
#include "../sopro/include/ATB/antTBar_geometry.h"


//--------------------------------- Callback Functions
//----- Position getter
static void TW_CALL getPositionCB(void* value, void* clientData)
{
    // get sceneObject
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    // get position from object
        *((float3*) value) =  tmpSO->getGeometry()->position();
}

//----- Position setter
static void TW_CALL setPositionCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float3 v = *((float3*)value);
    // create a new Geometry
        tmpSO->getGeometry()->setPosition(v);

}

//----- AreaPlane Dimensions X getter
static void TW_CALL getAreaDimensionsXCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<AreaPlane*>(tmpSO->getGeometry().get())->dimensionsX();
}
//----- AreaPlane Dimensions X setter
static void TW_CALL setAreaDimensionsXCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<AreaPlane> areaPlane = std::make_shared<AreaPlane>(tmpSO->getGeometry(), v, 0);
    tmpSO->setGeometry(areaPlane);
}

//----- AreaPlane Dimensions Y getter
static void TW_CALL getAreaDimensionsYCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<AreaPlane*>(tmpSO->getGeometry().get())->dimensionsY();
}
//----- AreaPlane Dimensions Y setter
static void TW_CALL setAreaDimensionsYCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<AreaPlane> areaPlane = std::make_shared<AreaPlane>(tmpSO->getGeometry(), v, 1);
    tmpSO->setGeometry(areaPlane);
}

//----- InfPlane Height getter
static void TW_CALL getInfHeightCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<InfinitePlane*>(tmpSO->getGeometry().get())->height();
}
//----- InfPlane Height setter
static void TW_CALL setInfHeightCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<InfinitePlane> infPlane = std::make_shared<InfinitePlane>(tmpSO->getGeometry(), v);
    tmpSO->setGeometry(infPlane);
}

//----- Sphere Radius getter
static void TW_CALL getSphereRadiusCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<Sphere*>(tmpSO->getGeometry().get())->radius();
}
//----- Sphere Radius setter
static void TW_CALL setSphereRadiusCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(tmpSO->getGeometry(), v);
    tmpSO->setGeometry(sphere);
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
            std::string nameVar1 = name + " Position";
            const char* nameVar1C = nameVar1.c_str();

            std::string nameVar2 = name + " DimensionsX";
            const char* nameVar2C = nameVar2.c_str();

            std::string nameVar3 = name + " DimensionsY";
            const char* nameVar3C = nameVar3.c_str();

            //---------- ATB variables
            // ATB Variable to set position and dimensions
            TwAddVarCB(bar, nameVar1C, TW_TYPE_DIR3F, setPositionCB, getPositionCB, scene->getSceneObject(i).get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setAreaDimensionsXCB, getAreaDimensionsXCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setAreaDimensionsYCB, getAreaDimensionsYCB, scene->getSceneObject(i).get(), grpNameFloatC);

        }
        //---------------- Geometry is InfinitePlane
        else if(scene->getSceneObject(i)->getGeometry()->getGeometryType() == BaseGeometry::INFINITEPLANE)
        {
            //---------- set name to specific variable
            std::string nameVar1 = name + " Position";
            const char* nameVar1C = nameVar1.c_str();

            std::string nameVar2 = name + " Height";
            const char* nameVar2C = nameVar2.c_str();

            //------------ ATB variables
            // ATB Variable for position and height
            TwAddVarCB(bar, nameVar1C, TW_TYPE_DIR3F, setPositionCB, getPositionCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setInfHeightCB, getInfHeightCB, scene->getSceneObject(i).get(), grpNameFloatC);

        }
        //---------------- Geometry is Sphere
        else if(scene->getSceneObject(i)->getGeometry()->getGeometryType() == BaseGeometry::SPHERE)
        {
            //---------- set name to specific variable
            std::string nameVar1 = name + " Position";
            const char* nameVar1C = nameVar1.c_str();

            std::string nameVar2 = name + " Radius";
            const char* nameVar2C = nameVar2.c_str();


            //------------ ATB variables
            // ATB Variable for position and radius
            TwAddVarCB(bar, nameVar1C, TW_TYPE_DIR3F, setPositionCB, getPositionCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setSphereRadiusCB, getSphereRadiusCB, scene->getSceneObject(i).get(), grpNameFloat0C);
        }

    }

}
/*
//--------------------------------- Variable init
void antTBarInit_material(SceneObject* scObj, TwBar *bar, std::string objName)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);

    //--------------- Generate names
    // Convert button name
    std::string nameLButton = objName;
    nameLButton += " into Lambert";
    const char* nameLButtonC = nameLButton.c_str();

    std::string namePButton = objName;
    namePButton += " into Phong";
    const char* namePButtonC = namePButton.c_str();

    std::string nameGButton = objName;
    nameGButton += " into Glass";
    const char* nameGButtonC = nameGButton.c_str();

    //----- name for object group
    std::string grpName = " group=' ";
    grpName += objName;
    grpName += "' ";
    const char* grpNameC = grpName.c_str();

    //-----name for object group + float steps extension
    // [0,1]
    std::string grpNameFloat1 = grpName + " min=0 max=1 step=0.025 ";
    const char* grpNameFloat1C = grpNameFloat1.c_str();

    // [0,)
    std::string grpNameFloat = grpName + " min=0 step=0.05 ";
    const char* grpNameFloatC = grpNameFloat.c_str();

    //----------------- Material is Lambert
    if(scObj->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        //---------- set name to specific variable
        std::string nameVar1 = objName + " Color";
        const char* nameVar1C = nameVar1.c_str();

        //---------- ATB variables
        // ATB Variable to change color
        TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, scObj, grpNameC);

        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, namePButtonC, phongButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);
    }
    //---------------- Material is Phong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        //---------- set name to specific variable
        std::string nameVar1 = objName + " Color";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = objName + " Ambient Coeff";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = objName + " Diffuse Coeff";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = objName + " Specular Coeff";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Shininess";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = objName + " Specularity";
        const char* nameVar6C = nameVar6.c_str();

        //------------ ATB variables
        // ATB Variable for color props
        TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, scObj, grpNameC);

        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, nameLButtonC, lambertButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);

        // ATB Variable for coeff props
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPhongAmbientCoeffCB, getPhongAmbientCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPhongDiffuseCoeffCB, getPhongDiffuseCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPhongSpecularCoeffCB, getPhongSpecularCoeffCB, scObj, grpNameFloat1C);

        // ATB Variable for shininess and specularity
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setPhongShininessCB, getPhongShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setPhongSpecularityCB, getPhongSpecularityCB, scObj, grpNameFloat1C);

    }
    //---------------- Material is Glass
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        //---------- set name to specific variable
        std::string nameVar1 = objName + " Color";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = objName + " Refractive Index";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = objName + " Specularity";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = objName + " Shininess";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Specular Coeff";
        const char* nameVar5C = nameVar5.c_str();


        //------------ ATB variables
        // ATB Variable for color props
        TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR4F, setColor4CB, getColor4CB, scObj, grpNameC);

        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, nameLButtonC, lambertButtonCB, scObj, grpNameC);
        TwAddButton(bar, namePButtonC, phongButtonCB, scObj, grpNameC);

        // ATB Variable for refractiveIndex and specularity
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setGlassRefractiveIdxCB, getGlassRefractiveIdxCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setGlassSpecularityCB, getGlassSpecularityCB, scObj, grpNameFloat1C);

        // ATB Variable for shininess and specularCoefficient
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setGlassShininessCB, getGlassShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setGlassSpecularCoeffCB, getGlassSpecularCoeffCB, scObj, grpNameFloat1C);
    }

}

//--------------------------------- Clear object specific variables
void antTBarRemoveVariable_material(SceneObject *scObj, TwBar *bar, std::string objName)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);

    //--------------- Generate names
    // Convert button name
    std::string nameLButton = scObj->getName();
    nameLButton += " into Lambert";
    const char* nameLButtonC = nameLButton.c_str();

    std::string namePButton = scObj->getName();
    namePButton += " into Phong";
    const char* namePButtonC = namePButton.c_str();

    std::string nameGButton = scObj->getName();
    nameGButton += " into Glass";
    const char* nameGButtonC = nameGButton.c_str();

    //----------------- Material is Lambert
    if(scObj->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {

        //---------- set name to specific variable
        std::string nameVar1 = objName + " Color";
        const char* nameVar1C = nameVar1.c_str();

        //---------- ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, namePButtonC);
        TwRemoveVar(bar, nameGButtonC);

        // ATB Variable to change color
        TwRemoveVar(bar, nameVar1C);
    }
    //---------------- Material is Phong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        //---------- set name to specific variable
        std::string nameVar1 = objName + " Color";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = objName + " Ambient Coeff";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = objName + " Diffuse Coeff";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = objName + " Specular Coeff";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Shininess";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = objName + " Specularity";
        const char* nameVar6C = nameVar6.c_str();

        //------------ ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, nameLButtonC);
        TwRemoveVar(bar, nameGButtonC);

        // ATB Variable for color props
        TwRemoveVar(bar, nameVar1C);

        // ATB Variable for coeff props
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);
        TwRemoveVar(bar, nameVar4C);

        // ATB Variable for shininess and specularity
        TwRemoveVar(bar, nameVar5C);
        TwRemoveVar(bar, nameVar6C);

    }
    //---------------- Material is Glass
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        //---------- set name to specific variable
        std::string nameVar1 = objName + " Color";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = objName + " Refractive Index";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = objName + " Specularity";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = objName + " Shininess";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Specular Coeff";
        const char* nameVar5C = nameVar5.c_str();


        //------------ ATB variables
        // ATB Variable for color props
        TwRemoveVar(bar, nameVar1C);

        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, nameLButtonC);
        TwRemoveVar(bar, namePButtonC);

        // ATB Variable for refractiveIndex and specularity
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);

        // ATB Variable for shininess and specularCoefficient
        TwRemoveVar(bar, nameVar4C);
        TwRemoveVar(bar, nameVar5C);
    }

}
*/
