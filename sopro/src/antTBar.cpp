#include "../include/antTBar.h"

//--------------------------------- Global variables to recall the init function
TwBar *gBar;
std::shared_ptr<Scene> gScene;

//--------------------------------- Callback Functions
//----- Color getter
static void TW_CALL getColorCB(void* value, void* clientData)
{
    // get sceneObject
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    // get color from specific sceneObject material
    switch(tmpSO->getMaterial()->getMaterialType())
    {
    case BaseMaterial::LAMBERT:
        *((float3*) value) =  static_cast<LambertMaterial*>(tmpSO->getMaterial().get())->color();
        break;
    case BaseMaterial::PHONG:
        *((float3*) value) =  static_cast<PhongMaterial*>(tmpSO->getMaterial().get())->color();
        break;
    }
}
//----- Color setter
static void TW_CALL setColorCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float3 v = *((float3*)value);
    // create a new LambertMaterial
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>(make_float3(v.x, v.y, v.z));
        // overwrite the old material with the new One
        tmpSO->setMaterial(lamMat);
    }
    else if (tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), make_float3(v.x, v.y, v.z));
        tmpSO->setMaterial(phongMat);
    }
}


//------------------------- Lambert
//----- Button to convert into Lambert
static void TW_CALL lambertButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    switch(tmpSO->getMaterial()->getMaterialType())
    {
    case BaseMaterial::PHONG:
        // save old material properties
        oldMat = "Phong";
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (make_float3(p->color().x, p->color().y, p->color().z));
        // overwrite the old Material with the new one
        tmpSO->setMaterial(lamMat);
        break;
    }
    // re-init new variables
    antTBarReInit(oldMat, tmpSO, gBar, tmpSO->getName());
}


//------------------------- Phong
//----- Button to convert into Phong
static void TW_CALL phongButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    switch(tmpSO->getMaterial()->getMaterialType())
    {
    case BaseMaterial::LAMBERT:
        // save old material properties
        oldMat = "Lambert";
        LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
                (make_float3(p->color().x, p->color().y, p->color().z));
        tmpSO->setMaterial(phongMat);
        break;
    }
    // re-init new variables
    antTBarReInit(oldMat, tmpSO, gBar, tmpSO->getName());
}
//----- AmbientCoeff getter
static void TW_CALL getPhongAmbientCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<PhongMaterial*>(tmpSO->getMaterial().get())->ambientCoeff();
}
//----- AmbientCoeff setter
static void TW_CALL setPhongAmbientCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), v, 1);
    tmpSO->setMaterial(phongMat);
}
//----- DiffuseCoeff getter
static void TW_CALL getPhongDiffuseCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<PhongMaterial*>(tmpSO->getMaterial().get())->diffuseCoeff();
}
//----- DiffuseCoeff setter
static void TW_CALL setPhongDiffuseCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), v, 2);
    tmpSO->setMaterial(phongMat);
}
//----- SpecularCoeff getter
static void TW_CALL getPhongSpecularCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<PhongMaterial*>(tmpSO->getMaterial().get())->specularCoeff();
}
//----- DiffuseCoeff setter
static void TW_CALL setPhongSpecularCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), v, 3);
    tmpSO->setMaterial(phongMat);
}
//----- Shininess getter
static void TW_CALL getPhongShininessCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<PhongMaterial*>(tmpSO->getMaterial().get())->shininess();
}
//----- Shininess setter
static void TW_CALL setPhongShininessCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), v, 4);
    tmpSO->setMaterial(phongMat);
}
//----- Specularity getter
static void TW_CALL getPhongSpecularityCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<PhongMaterial*>(tmpSO->getMaterial().get())->specularity();
}
//----- Specularity setter
static void TW_CALL setPhongSpecularityCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), v, 5);
    tmpSO->setMaterial(phongMat);
}

//--------------------------------- Basic variable init
void antTBar(std::shared_ptr<Scene> scene, TwBar *bar)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);
    gScene = scene;

    for(int i = 0; i < scene->getSceneObjectCount(); i++)
    {
        //--------------- Generate names
        // object name
        std::string name = scene->getSceneObject(i)->getName();

        // Convert button name
        std::string nameLButton = scene->getSceneObject(i)->getName();
        nameLButton += " into Lambert";
        const char* nameLButtonC = nameLButton.c_str();
        std::string namePButton = scene->getSceneObject(i)->getName();
        namePButton += " into Phong";
        const char* namePButtonC = namePButton.c_str();

        //----- name for object group
        std::string grpName = " group=' ";
        grpName += scene->getSceneObject(i)->getName();
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
        if(scene->getSceneObject(i)->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT){
            //---------- set name to specific variable
            std::string nameVar1 = name + " Color";
            const char* nameVar1C = nameVar1.c_str();

            //---------- ATB variables
            // ATB Variable to change color
            TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Buttons to convert into another Material Type
            TwAddButton(bar, namePButtonC, phongButtonCB, scene->getSceneObject(i).get(), grpNameC);

        }
        //---------------- Material is Phong
        else if(scene->getSceneObject(i)->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
        {
            //---------- set name to specific variable
            std::string nameVar1 = name + " Color";
            const char* nameVar1C = nameVar1.c_str();

            std::string nameVar2 = name + " Ambient Coeff";
            const char* nameVar2C = nameVar2.c_str();

            std::string nameVar3 = name + " Diffuse Coeff";
            const char* nameVar3C = nameVar3.c_str();

            std::string nameVar4 = name + " Specular Coeff";
            const char* nameVar4C = nameVar4.c_str();

            std::string nameVar5 = name + " Shininess";
            const char* nameVar5C = nameVar5.c_str();

            std::string nameVar6 = name + " Specularity";
            const char* nameVar6C = nameVar6.c_str();

            //------------ ATB variables
            // ATB Variable for color props
            TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Buttons to convert into another Material Type
            TwAddButton(bar, nameLButtonC, lambertButtonCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Variable for coeff props
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPhongAmbientCoeffCB, getPhongAmbientCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
            TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPhongDiffuseCoeffCB, getPhongDiffuseCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
            TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPhongSpecularCoeffCB, getPhongSpecularCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);

            // ATB Variable for shininess and specularity
            TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setPhongShininessCB, getPhongShininessCB, scene->getSceneObject(i).get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setPhongSpecularityCB, getPhongSpecularityCB, scene->getSceneObject(i).get(), grpNameFloatC);

        }

    }

}

//--------------------------------- Variable init
void antTBarInit(SceneObject* scObj, TwBar *bar, std::string objName)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);

    //--------------- Generate names
    // object name
    std::string name = objName;

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
        // Convert-button name
        std::string namePButton = objName;
        namePButton += " into Phong";
        const char* namePButtonC = namePButton.c_str();

        //---------- set name to specific variable
        std::string nameVar1 = name + " Color";
        const char* nameVar1C = nameVar1.c_str();

        //---------- ATB variables
        // ATB Variable to change color
        TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, scObj, grpNameC);

        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, namePButtonC, phongButtonCB, scObj, grpNameC);
    }
    //---------------- Material is Phong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        // Convert-button name
        std::string nameLButton = objName;
        nameLButton += " into Lambert";
        const char* nameLButtonC = nameLButton.c_str();

        //---------- set name to specific variable
        std::string nameVar1 = name + " Color";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = name + " Ambient Coeff";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = name + " Diffuse Coeff";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = name + " Specular Coeff";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = name + " Shininess";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = name + " Specularity";
        const char* nameVar6C = nameVar6.c_str();

        //------------ ATB variables
        // ATB Variable for color props
        TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, scObj, grpNameC);

        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, nameLButtonC, lambertButtonCB, scObj, grpNameC);

        // ATB Variable for coeff props
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPhongAmbientCoeffCB, getPhongAmbientCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPhongDiffuseCoeffCB, getPhongDiffuseCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPhongSpecularCoeffCB, getPhongSpecularCoeffCB, scObj, grpNameFloat1C);

        // ATB Variable for shininess and specularity
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setPhongShininessCB, getPhongShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setPhongSpecularityCB, getPhongSpecularityCB, scObj, grpNameFloatC);

    }

}

//--------------------------------- Clear object specific variables
void antTBarRemoveVariable(SceneObject *scObj, TwBar *bar, std::string objName)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);

    //--------------- Generate names
    // object name
    std::string name = objName;

    //----------------- Material is Lambert
    if(scObj->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        //Convert-button name
        std::string namePButton = objName;
        namePButton += " into Phong";
        const char* namePButtonC = namePButton.c_str();

        //---------- set name to specific variable
        std::string nameVar1 = name + " Color";
        const char* nameVar1C = nameVar1.c_str();

        //---------- ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, namePButtonC);

        // ATB Variable to change color
        TwRemoveVar(bar, nameVar1C);
    }
    //---------------- Material is Phong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        // Convert-button name
        std::string nameLButton = objName;
        nameLButton += " into Lambert";
        const char* nameLButtonC = nameLButton.c_str();

        //---------- set name to specific variable
        std::string nameVar1 = name + " Color";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = name + " Ambient Coeff";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = name + " Diffuse Coeff";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = name + " Specular Coeff";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = name + " Shininess";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = name + " Specularity";
        const char* nameVar6C = nameVar6.c_str();

        //------------ ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, nameLButtonC);

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

}

//--------------------------------- Variable re-init
void antTBarReInit(std::string oldMat, SceneObject* scObj, TwBar *bar, std::string objName)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);

    //--------------- Generate names
    // object name
    std::string name = objName;

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

    //------------------------ Clear variables
    //----------------- Material is Lambert
    if(oldMat == "Lambert")
    {
        //Convert-button name
        std::string namePButton = objName;
        namePButton += " into Phong";
        const char* namePButtonC = namePButton.c_str();

        //---------- ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, namePButtonC);
    }
    //---------------- Material is Phong
    else if(oldMat == "Phong")
    {
        // Convert-button name
        std::string nameLButton = objName;
        nameLButton += " into Lambert";
        const char* nameLButtonC = nameLButton.c_str();

        //---------- set name to specific variable
        std::string nameVar2 = name + " Ambient Coeff";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = name + " Diffuse Coeff";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = name + " Specular Coeff";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = name + " Shininess";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = name + " Specularity";
        const char* nameVar6C = nameVar6.c_str();

        //------------ ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, nameLButtonC);

        // ATB Variable for coeff props
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);
        TwRemoveVar(bar, nameVar4C);

        // ATB Variable for shininess and specularity
        TwRemoveVar(bar, nameVar5C);
        TwRemoveVar(bar, nameVar6C);

    }

    //------------------------ Re-init variables
    //----------------- Material is Lambert
    if(scObj->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        // Convert-button name
        std::string namePButton = objName;
        namePButton += " into Phong";
        const char* namePButtonC = namePButton.c_str();

        //---------- ATB variables
        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, namePButtonC, phongButtonCB, scObj, grpNameC);
    }
    //---------------- Material is Phong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        // Convert-button name
        std::string nameLButton = objName;
        nameLButton += " into Lambert";
        const char* nameLButtonC = nameLButton.c_str();

        std::string nameVar2 = name + " Ambient Coeff";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar3 = name + " Diffuse Coeff";
        const char* nameVar3C = nameVar3.c_str();

        std::string nameVar4 = name + " Specular Coeff";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = name + " Shininess";
        const char* nameVar5C = nameVar5.c_str();

        std::string nameVar6 = name + " Specularity";
        const char* nameVar6C = nameVar6.c_str();

        //------------ ATB variables
        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, nameLButtonC, lambertButtonCB, scObj, grpNameC);

        // ATB Variable for coeff props
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPhongAmbientCoeffCB, getPhongAmbientCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPhongDiffuseCoeffCB, getPhongDiffuseCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPhongSpecularCoeffCB, getPhongSpecularCoeffCB, scObj, grpNameFloat1C);

        // ATB Variable for shininess and specularity
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setPhongShininessCB, getPhongShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setPhongSpecularityCB, getPhongSpecularityCB, scObj, grpNameFloatC);

    }

}

