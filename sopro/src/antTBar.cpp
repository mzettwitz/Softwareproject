#include "../include/antTBar.h"

// TODO: fix gScene pointer to renew the bar

TwBar *gBar;
std::shared_ptr<Scene> gScene;

// Lambert
// Lambert getter
static void TW_CALL getLambertCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float3*) value) =  static_cast<LambertMaterial*>(tmpSO->getMaterial().get())->color();
}
// Lambert setter
static void TW_CALL setLambertCB(const void* value, void* clientData)
{
    // save params in temporary variable
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float3 v = *((float3*)value);
    // create a new LambertMaterial
    std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>(make_float3(v.x, v.y, v.z));

    // overwrite the old Material with the new one
    tmpSO->setMaterial(lamMat);
}
// Button to convert into Lambert
static void TW_CALL lambertButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    switch(tmpSO->getMaterial()->getMaterialType())
    {
    case BaseMaterial::PHONG:
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (make_float3(p->ambientColor().x, p->ambientColor().y, p->ambientColor().z));
        // overwrite the old Material with the new one
        tmpSO->setMaterial(lamMat);
        break;
    }

    TwRemoveAllVars(gBar);
    antTBar(gScene, gBar);
    TwRefreshBar(gBar);
}


// Phong
// Button to convert into Lambert
static void TW_CALL phongButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    switch(tmpSO->getMaterial()->getMaterialType())
    {
    case BaseMaterial::LAMBERT:
        // save old material properties
        LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
        // write old properties into new material
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
                (make_float3(p->color().x, p->color().y, p->color().z));
        // overwrite the old material with the new one
        tmpSO->setMaterial(phongMat);
        break;
    }

    TwRemoveAllVars(gBar);
    antTBar(gScene, gBar);
}


// Variable init
void antTBar(std::shared_ptr<Scene> scene, TwBar *bar)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);
    gScene = scene;

    for(int i = 0; i < scene->getSceneObjectCount(); i++)
    {
        // names for bar variables
        std::string name = scene->getSceneObject(i)->getName();

        std::string nameLButton = scene->getSceneObject(i)->getName();
        nameLButton += " into Lambert";
        const char* nameLButtonC = nameLButton.c_str();
        std::string namePButton = scene->getSceneObject(i)->getName();
        namePButton += " into Phong";
        const char* namePButtonC = namePButton.c_str();

        // name for object group
        std::string grpName = " group=' ";
        grpName += scene->getSceneObject(i)->getName();
        grpName += "' ";
        const char* grpNameC = grpName.c_str();


        if(scene->getSceneObject(i)->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT){
            // set name to specific variable
            std::string nameVar1 = name + " Color";
            const char* nameVar1C = nameVar1.c_str();

            // ATB Buttons to convert into antother Material Type
            TwAddButton(bar, namePButtonC, phongButtonCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Variable to change color
            TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setLambertCB, getLambertCB, scene->getSceneObject(i).get(), grpNameC);
        }

    }

}




