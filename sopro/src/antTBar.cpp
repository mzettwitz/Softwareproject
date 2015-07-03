#include "../include/antTBar.h"

//--------------------------------- Global variables to recall the init function
TwBar *gBar;
std::shared_ptr<Scene> gScene;

//--------------------------------- Callback Functions
//------------------------- Lambert
//----- Button to convert into Lambert
static void TW_CALL lambertButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    switch(tmpSO->getMaterial()->getMaterialType())
    {
    case BaseMaterial::PHONG:
        // save old material properties
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (make_float3(p->color().x, p->color().y, p->color().z));
        // overwrite the old Material with the new one
        tmpSO->setMaterial(lamMat);
        break;
    }
    // remove all variables and re-initialize all variables by calling init function
    TwRemoveAllVars(gBar);
    antTBar(gScene, gBar);
}
//----- Lambert color getter
static void TW_CALL getLambertCB(void* value, void* clientData)
{
    // get sceneObject
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    // get color from specific sceneObject material
    *((float3*) value) =  static_cast<LambertMaterial*>(tmpSO->getMaterial().get())->color();
}
//----- Lambert color setter
static void TW_CALL setLambertCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float3 v = *((float3*)value);
    // create a new LambertMaterial
    std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>(make_float3(v.x, v.y, v.z));
    // overwrite the old material with the new One
    tmpSO->setMaterial(lamMat);
}


//------------------------- Phong
//----- Button to convert into Phong
static void TW_CALL phongButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    switch(tmpSO->getMaterial()->getMaterialType())
    {
    case BaseMaterial::LAMBERT:
         LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
         std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
               (make_float3(p->color().x, p->color().y, p->color().z));
        tmpSO->setMaterial(phongMat);
        break;
    }
    TwRemoveAllVars(gBar);
    antTBar(gScene, gBar);
}
//----- Color getter
static void TW_CALL getPhongColorCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float3*) value) =  static_cast<PhongMaterial*>(tmpSO->getMaterial().get())->color();
}
//----- Color setter
static void TW_CALL setPhongColorCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float3 v = *((float3*)value);
    std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), make_float3(v.x, v.y, v.z));
    tmpSO->setMaterial(phongMat);
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

//--------------------------------- Variable init
void antTBar(std::shared_ptr<Scene> scene, TwBar *bar)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);
    gScene = scene;

    if(gScene == scene)
        std::cout << "OK";
    else std::cout << "FUCK";

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
            // ATB Buttons to convert into antother Material Type
            TwAddButton(bar, namePButtonC, phongButtonCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Variable to change color
            TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setLambertCB, getLambertCB, scene->getSceneObject(i).get(), grpNameC);
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
            // ATB Buttons to convert into antother Material Type
            TwAddButton(bar, nameLButtonC, lambertButtonCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Variable for color props
            TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setPhongColorCB, getPhongColorCB, scene->getSceneObject(i).get(), grpNameC);

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




