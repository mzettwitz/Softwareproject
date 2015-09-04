#include "../sopro/include/ATB/antTBar.h"
#include "../sopro/include/ATB/antTBar_material.h"

//--------------------------------- Global variables to recall the init function
TwBar *gBar;

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
    case BaseMaterial::GLASS:
        *((float3*) value) =  static_cast<GlassMaterial*>(tmpSO->getMaterial().get())->color();
        break;
    case BaseMaterial::BLINNPHONG:
        *((float3*) value) =  static_cast<BlinnPhongMaterial*>(tmpSO->getMaterial().get())->color();
        break;
    case BaseMaterial::ASHIKHMINSHIRLEY:
        *((float3*) value) =  static_cast<AshikhminShirleyMaterial*>(tmpSO->getMaterial().get())->color();
        break;
    case BaseMaterial::COOKTORRANCE:
        *((float3*) value) =  static_cast<CookTorranceMaterial*>(tmpSO->getMaterial().get())->color();
        break;
    case BaseMaterial::WARD:
        *((float3*) value) =  static_cast<WardMaterial*>(tmpSO->getMaterial().get())->color();
        break;
    }
}

//----- Color setter
static void TW_CALL setColorCB(const void* value, void* clientData)
{
    // save params in temporary pointer
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float3 v = *((float3*)value);
    // create a new Material
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>(v);
        // overwrite the old material with the new One
        tmpSO->setMaterial(lamMat);
    }
    else if (tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), v);
        tmpSO->setMaterial(phongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>(tmpSO->getMaterial(), v);
        tmpSO->setMaterial(glassMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        std::shared_ptr<BlinnPhongMaterial> blinnMat = std::make_shared<BlinnPhongMaterial>(tmpSO->getMaterial(), v);
        tmpSO->setMaterial(blinnMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        std::shared_ptr<AshikhminShirleyMaterial> AshiMat = std::make_shared<AshikhminShirleyMaterial>(tmpSO->getMaterial(), v);
        tmpSO->setMaterial(AshiMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        std::shared_ptr<CookTorranceMaterial> cookMat = std::make_shared<CookTorranceMaterial>(tmpSO->getMaterial(), v);
        tmpSO->setMaterial(cookMat);
    }
}

//------------------------- Lambert
//----- Button to convert into Lambert
static void TW_CALL lambertButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        // save old material properties
        oldMat = "Phong";
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (p->color());
        // overwrite the old Material with the new one
        tmpSO->setMaterial(lamMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        // save old material properties
        oldMat = "Glass";
        GlassMaterial* p = (GlassMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (p->color());
        // overwrite the old Material with the new one
        tmpSO->setMaterial(lamMat);
    }
    // re-init new variables
    antTBarReInit_material(oldMat, tmpSO, gBar, tmpSO->getName());
}


//------------------------- Phong
//----- Button to convert into Phong
static void TW_CALL phongButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        // save old material properties
        oldMat = "Lambert";
        LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
                (p->color());
        tmpSO->setMaterial(phongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        // save old material properties
        oldMat = "Glass";
        GlassMaterial* p = (GlassMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
                (p->color(), p->specularCoeff(), p->shininess(), 1);
        tmpSO->setMaterial(phongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        // save old material properties
        oldMat = "BlinnPhong";
        BlinnPhongMaterial* p = (BlinnPhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(p);
        tmpSO->setMaterial(phongMat);
    }
    // re-init new variables
    antTBarReInit_material(oldMat, tmpSO, gBar, tmpSO->getName());
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
//----- SpecularCoeff setter
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

//------------------------- Glass
//----- Button to convert into Glass
static void TW_CALL glassButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        // save old material properties
        oldMat = "Lambert";
        LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>
                (p->color());
        tmpSO->setMaterial(glassMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        // save old material properties
        oldMat = "Phong";
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>
                (p->color(), p->shininess(), p->specularCoeff());
        tmpSO->setMaterial(glassMat);
    }
    // re-init new variables
    antTBarReInit_material(oldMat, tmpSO, gBar, tmpSO->getName());
}
//----- RefractiveIndex getter
static void TW_CALL getGlassRefractiveIdxCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<GlassMaterial*>(tmpSO->getMaterial().get())->refractiveIdx();
}
//----- RefractiveIndex setter
static void TW_CALL setGlassRefractiveIdxCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>(tmpSO->getMaterial(), v, 1);
    tmpSO->setMaterial(glassMat);
}
//----- Shininess getter
static void TW_CALL getGlassShininessCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<GlassMaterial*>(tmpSO->getMaterial().get())->shininess();
}
//----- Shininess setter
static void TW_CALL setGlassShininessCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>(tmpSO->getMaterial(), v, 3);
    tmpSO->setMaterial(glassMat);
}
//----- SpecularCoeff getter
static void TW_CALL getGlassSpecularCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<GlassMaterial*>(tmpSO->getMaterial().get())->specularCoeff();
}
//----- SpecularCoeff setter
static void TW_CALL setGlassSpecularCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>(tmpSO->getMaterial(), v, 4);
    tmpSO->setMaterial(glassMat);
}

//--------------------------------- Basic variable init
void antTBar_material(std::shared_ptr<Scene> scene, TwBar *bar)
{
    // save params into global to refresh the bar after conversion
    gBar = static_cast<TwBar*>(bar);

    for(int i = 0; i < scene->getSceneObjectCount(); i++)
    {
        //--------------- Generate names
        // object name
        std::string name = scene->getSceneObject(i)->getName();

        // Convert button name
        std::string nameLButton = name;
        nameLButton += " into Lambert";
        const char* nameLButtonC = nameLButton.c_str();

        std::string namePButton = name;
        namePButton += " into Phong";
        const char* namePButtonC = namePButton.c_str();

        std::string nameGButton = name;
        nameGButton += " into Glass";
        const char* nameGButtonC = nameGButton.c_str();

        //----- name for object group
        std::string grpName = " group=' ";
        grpName += name;
        grpName += "' ";
        const char* grpNameC = grpName.c_str();

        //-----name for object group + float steps extension
        // [0,1]
        std::string grpNameFloat1 = grpName + " min=0 max=1 step=0.025 ";
        const char* grpNameFloat1C = grpNameFloat1.c_str();

        // [0,5]
        std::string grpNameFloat5 = grpName + " min=0 max=5 step=0.025 ";
        const char* grpNameFloat5C = grpNameFloat5.c_str();

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
            TwAddButton(bar, nameGButtonC, glassButtonCB, scene->getSceneObject(i).get(), grpNameC);

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
            TwAddButton(bar, nameGButtonC, glassButtonCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Variable for coeff props
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPhongAmbientCoeffCB, getPhongAmbientCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
            TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPhongDiffuseCoeffCB, getPhongDiffuseCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
            TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPhongSpecularCoeffCB, getPhongSpecularCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);

            // ATB Variable for shininess and specularity
            TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setPhongShininessCB, getPhongShininessCB, scene->getSceneObject(i).get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setPhongSpecularityCB, getPhongSpecularityCB, scene->getSceneObject(i).get(), grpNameFloat1C);
        }
        //---------------- Material is Glass
        else if(scene->getSceneObject(i)->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
        {
            //---------- set name to specific variable
            std::string nameVar1 = name + " Color";
            const char* nameVar1C = nameVar1.c_str();

            std::string nameVar2 = name + " Refractive Index";
            const char* nameVar2C = nameVar2.c_str();

            std::string nameVar4 = name + " Shininess";
            const char* nameVar4C = nameVar4.c_str();

            std::string nameVar5 = name + " Specular Coeff";
            const char* nameVar5C = nameVar5.c_str();

            //------------ ATB variables
            // ATB Variable for color props
            TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Buttons to convert into another Material Type
            TwAddButton(bar, nameLButtonC, lambertButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, namePButtonC, phongButtonCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Variable for refractiveIndex
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setGlassRefractiveIdxCB, getGlassRefractiveIdxCB, scene->getSceneObject(i).get(), grpNameFloat5C);

            // ATB Variable for shininess and specularCoefficient
            TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setGlassShininessCB, getGlassShininessCB, scene->getSceneObject(i).get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setGlassSpecularCoeffCB, getGlassSpecularCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
        }
    }

}

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

    // [0,5]
    std::string grpNameFloat5 = grpName + " min=0 max=5 step=0.025 ";
    const char* grpNameFloat5C = grpNameFloat5.c_str();

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

        std::string nameVar4 = objName + " Shininess";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Specular Coeff";
        const char* nameVar5C = nameVar5.c_str();


        //------------ ATB variables
        // ATB Variable for color props
        TwAddVarCB(bar, nameVar1C, TW_TYPE_COLOR3F, setColorCB, getColorCB, scObj, grpNameC);

        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, nameLButtonC, lambertButtonCB, scObj, grpNameC);
        TwAddButton(bar, namePButtonC, phongButtonCB, scObj, grpNameC);

        // ATB Variable for refractiveIndex
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setGlassRefractiveIdxCB, getGlassRefractiveIdxCB, scObj, grpNameFloat5C);

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

        // ATB Variable for refractiveIndex
        TwRemoveVar(bar, nameVar2C);

        // ATB Variable for shininess and specularCoefficient
        TwRemoveVar(bar, nameVar4C);
        TwRemoveVar(bar, nameVar5C);
    }

}

//--------------------------------- Variable re-init
void antTBarReInit_material(std::string oldMat, SceneObject* scObj, TwBar *bar, std::string objName)
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

    //----- name for object group
    std::string grpName = " group=' ";
    grpName += objName;
    grpName += "' ";
    const char* grpNameC = grpName.c_str();

    //-----name for object group + float steps extension
    // [0,1]
    std::string grpNameFloat1 = grpName + " min=0 max=1 step=0.025 ";
    const char* grpNameFloat1C = grpNameFloat1.c_str();

    // [0,5]
    std::string grpNameFloat5 = grpName + " min=0 max=5 step=0.025 ";
    const char* grpNameFloat5C = grpNameFloat5.c_str();

    // [0,)
    std::string grpNameFloat = grpName + " min=0 step=0.05 ";
    const char* grpNameFloatC = grpNameFloat.c_str();

    //------------------------ Clear variables
    //----------------- Material was Lambert
    if(oldMat == "Lambert")
    {
        //---------- ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, namePButtonC);
        TwRemoveVar(bar, nameGButtonC);
    }
    //---------------- Material was Phong
    else if(oldMat == "Phong")
    {
        //---------- set name to specific variable
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

        // ATB Variable for coeff props
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);
        TwRemoveVar(bar, nameVar4C);

        // ATB Variable for shininess and specularity
        TwRemoveVar(bar, nameVar5C);
        TwRemoveVar(bar, nameVar6C);

    }
    //---------------- Material was Glass
    else if(oldMat == "Glass")
    {
        //---------- set name to specific variable
        std::string nameVar2 = objName + " Refractive Index";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar4 = objName + " Shininess";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Specular Coeff";
        const char* nameVar5C = nameVar5.c_str();

        //------------ ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, nameLButtonC);
        TwRemoveVar(bar, namePButtonC);

        // ATB Variable for refractiveIndex
        TwRemoveVar(bar, nameVar2C);

        // ATB Variable for shininess and specularCoefficient
        TwRemoveVar(bar, nameVar4C);
        TwRemoveVar(bar, nameVar5C);
    }

    //------------------------ Re-init variables
    //----------------- Material is Lambert
    if(scObj->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        //---------- ATB variables
        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, namePButtonC, phongButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);
    }
    //---------------- Material is Phong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
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
        std::string nameVar1 = objName + " Color";
        const char* nameVar1C = nameVar1.c_str();

        std::string nameVar2 = objName + " Refractive Index";
        const char* nameVar2C = nameVar2.c_str();

        std::string nameVar4 = objName + " Shininess";
        const char* nameVar4C = nameVar4.c_str();

        std::string nameVar5 = objName + " Specular Coeff";
        const char* nameVar5C = nameVar5.c_str();

        //------------ ATB variables
        // ATB Buttons to convert into another Material Type
        TwAddButton(bar, nameLButtonC, lambertButtonCB, scObj, grpNameC);
        TwAddButton(bar, namePButtonC, phongButtonCB, scObj, grpNameC);

        // ATB Variable for refractiveIndex
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setGlassRefractiveIdxCB, getGlassRefractiveIdxCB, scObj, grpNameFloat5C);

        // ATB Variable for shininess and specularCoefficient
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setGlassShininessCB, getGlassShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setGlassSpecularCoeffCB, getGlassSpecularCoeffCB, scObj, grpNameFloat1C);
    }

}
