#include "../sopro/include/ATB/antTBar.h"
#include "../sopro/include/ATB/antTBar_material.h"

/*
 * TwDefine(" mybar/Blue   group=Color     \n"    // Blue is moved into group Color
         " mybar/Color  group=Properties  ");  // group Color is moved into group Properties
 */

// typdefs for shorter code
typedef AshikhminShirleyMaterial ASM;
typedef CookTorranceMaterial CTM;
typedef BlinnPhongMaterial BPM;

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
        *((float3*) value) =  static_cast<BPM*>(tmpSO->getMaterial().get())->color();
        break;
    case BaseMaterial::ASHIKHMINSHIRLEY:
        *((float3*) value) =  static_cast<ASM*>(tmpSO->getMaterial().get())->color();
        break;
    case BaseMaterial::COOKTORRANCE:
        *((float3*) value) =  static_cast<CTM*>(tmpSO->getMaterial().get())->color();
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
    float3 col = *((float3*)value);
    // create a new Material
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>(col);
        // overwrite the old material with the new One
        tmpSO->setMaterial(lamMat);
    }
    else if (tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(tmpSO->getMaterial(), col);
        tmpSO->setMaterial(phongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>(tmpSO->getMaterial(), col);
        tmpSO->setMaterial(glassMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        std::shared_ptr<BPM> blinnMat = std::make_shared<BPM>(tmpSO->getMaterial(), col);
        tmpSO->setMaterial(blinnMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        std::shared_ptr<ASM> AshiMat = std::make_shared<ASM>(tmpSO->getMaterial(), col);
        tmpSO->setMaterial(AshiMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        std::shared_ptr<CTM> cookMat = std::make_shared<CTM>(tmpSO->getMaterial(), col);
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
        oldMat = "Glass";
        GlassMaterial* p = (GlassMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (p->color());
        tmpSO->setMaterial(lamMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        oldMat = "BlinnPhong";
        BPM* p = (BPM*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (p->color());
        tmpSO->setMaterial(lamMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        oldMat = "AshikhminShirley";
        ASM* p = (ASM*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (p->color());
        tmpSO->setMaterial(lamMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        oldMat = "CookTorrance";
        CTM* p = (CTM*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (p->color());
        tmpSO->setMaterial(lamMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::WARD)
    {
        oldMat = "Ward";
        WardMaterial* p = (WardMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>
                (p->color());
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
        oldMat = "Glass";
        GlassMaterial* p = (GlassMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
                (p->color(), p->specularCoeff(), p->shininess(), 1);
        tmpSO->setMaterial(phongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        oldMat = "BlinnPhong";
        BPM* p = (BPM*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
                (p->color(), p->ambientCoeff(), p->diffuseCoeff(), p->specularCoeff(), p->shininess(), p->specularity());
        tmpSO->setMaterial(phongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        oldMat = "AshikhminShirley";
        ASM* p = (ASM*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
                (p->color(), p->rd(), p->rs(), 3);
        tmpSO->setMaterial(phongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        oldMat = "CookTorrance";
        CTM* p = (CTM*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>
                (p->color(), p->diffuseCoeff(), p->reflectance(), 2);
        tmpSO->setMaterial(phongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::WARD)
    {
        oldMat = "WARD";
        WardMaterial* p = (WardMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<PhongMaterial> phongMat = std::make_shared<PhongMaterial>(p->color(), p->diffuseCoeff());
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


//------------------------- BlinnPhong
//----- Button to convert into BlinnPhong
static void TW_CALL bPButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        // save old material properties
        oldMat = "Lambert";
        LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>
                (p->color());
        tmpSO->setMaterial(blinnPhongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        oldMat = "Glass";
        GlassMaterial* p = (GlassMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>
                (p->color(), p->specularCoeff(), p->shininess(), 1);
        tmpSO->setMaterial(blinnPhongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        oldMat = "Phong";
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>
                (p->color(), p->ambientCoeff(), p->diffuseCoeff(), p->specularCoeff(), p->shininess(), p->specularity());
        tmpSO->setMaterial(blinnPhongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        oldMat = "AshikhminShirley";
        ASM* p = (ASM*)tmpSO->getMaterial().get();
        std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>
                (p->color(), p->rd(), p->rs(), 3);
        tmpSO->setMaterial(blinnPhongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        oldMat = "CookTorrance";
        CTM* p = (CTM*)tmpSO->getMaterial().get();
        std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>
                (p->color(), p->diffuseCoeff(), p->reflectance(), 2);
        tmpSO->setMaterial(blinnPhongMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::WARD)
    {
        oldMat = "WARD";
        WardMaterial* p = (WardMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>(p->color(), p->diffuseCoeff());
        tmpSO->setMaterial(blinnPhongMat);
    }
    // re-init new variables
    antTBarReInit_material(oldMat, tmpSO, gBar, tmpSO->getName());
}
//----- AmbientCoeff getter
static void TW_CALL getBPAmbientCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<BPM*>(tmpSO->getMaterial().get())->ambientCoeff();
}
//----- AmbientCoeff setter
static void TW_CALL setBPAmbientCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>(tmpSO->getMaterial(), v, 1);
    tmpSO->setMaterial(blinnPhongMat);
}
//----- DiffuseCoeff getter
static void TW_CALL getBPDiffuseCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<BPM*>(tmpSO->getMaterial().get())->diffuseCoeff();
}
//----- DiffuseCoeff setter
static void TW_CALL setBPDiffuseCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>(tmpSO->getMaterial(), v, 2);
    tmpSO->setMaterial(blinnPhongMat);
}
//----- SpecularCoeff getter
static void TW_CALL getBPSpecularCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<BPM*>(tmpSO->getMaterial().get())->specularCoeff();
}
//----- SpecularCoeff setter
static void TW_CALL setBPSpecularCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>(tmpSO->getMaterial(), v, 3);
    tmpSO->setMaterial(blinnPhongMat);
}
//----- Shininess getter
static void TW_CALL getBPShininessCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<BPM*>(tmpSO->getMaterial().get())->shininess();
}
//----- Shininess setter
static void TW_CALL setBPShininessCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>(tmpSO->getMaterial(), v, 4);
    tmpSO->setMaterial(blinnPhongMat);
}
//----- Specularity getter
static void TW_CALL getBPSpecularityCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<BPM*>(tmpSO->getMaterial().get())->specularity();
}
//----- Specularity setter
static void TW_CALL setBPSpecularityCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<BPM> blinnPhongMat = std::make_shared<BPM>(tmpSO->getMaterial(), v, 5);
    tmpSO->setMaterial(blinnPhongMat);
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
        oldMat = "Phong";
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>
                (p->color(), p->shininess(), p->specularCoeff());
        tmpSO->setMaterial(glassMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        oldMat = "BlinnPhong";
        BPM* p = (BPM*)tmpSO->getMaterial().get();
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>
                (p->color(), p->shininess(), p->specularCoeff());
        tmpSO->setMaterial(glassMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        oldMat = "AshikhminShirley";
        ASM* p = (ASM*)tmpSO->getMaterial().get();
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>
                (p->color(), p->rs());
        tmpSO->setMaterial(glassMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        oldMat = "CookTorrance";
        CTM* p = (CTM*)tmpSO->getMaterial().get();
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>
                (p->color());
        tmpSO->setMaterial(glassMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::WARD)
    {
        oldMat = "Ward";
        WardMaterial* p = (WardMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<GlassMaterial> glassMat = std::make_shared<GlassMaterial>
                (p->color());
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


//------------------------- Ashikhmin-Shirley
//----- Button to convert into AshikhminShirley
static void TW_CALL aSButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        // save old material properties
        oldMat = "Lambert";
        LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>
                (p->color());
        tmpSO->setMaterial(ashikhminShirleyMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        oldMat = "Phong";
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>
                (p->color(), p->diffuseCoeff(), p->specularCoeff());
        tmpSO->setMaterial(ashikhminShirleyMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        oldMat = "BlinnPhong";
        BPM* p = (BPM*)tmpSO->getMaterial().get();
        std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>
                (p->color(), p->diffuseCoeff(), p->specularCoeff());
        tmpSO->setMaterial(ashikhminShirleyMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        oldMat = "Glass";
        GlassMaterial* p = (GlassMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>
                (p->color(), p->specularCoeff(), (short)2);
        tmpSO->setMaterial(ashikhminShirleyMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::WARD)
    {
        oldMat = "Ward";
        WardMaterial* p = (WardMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>
                (p->color(), p->diffuseCoeff(), (short)1);
        tmpSO->setMaterial(ashikhminShirleyMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        oldMat = "CookTorrance";
        CTM* p = (CTM*)tmpSO->getMaterial().get();
        std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>
                (p->color(), p->diffuseCoeff());
        tmpSO->setMaterial(ashikhminShirleyMat);
    }
    // re-init new variables
    antTBarReInit_material(oldMat, tmpSO, gBar, tmpSO->getName());
}
//----- Anisotropic U getter
static void TW_CALL getASAnisotropicUCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<ASM*>(tmpSO->getMaterial().get())->anisotropicFactorU();
}
//----- Anisotropic U setter
static void TW_CALL setASAnisotropicUCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>(tmpSO->getMaterial(), v, 1);
    tmpSO->setMaterial(ashikhminShirleyMat);
}
//----- Anisotropic V getter
static void TW_CALL getASAnisotropicVCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<ASM*>(tmpSO->getMaterial().get())->anisotropicFactorV();
}
//----- Anisotropic V setter
static void TW_CALL setASAnisotropicVCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>(tmpSO->getMaterial(), v, 2);
    tmpSO->setMaterial(ashikhminShirleyMat);
}
//----- Rs getter
static void TW_CALL getASRsCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<ASM*>(tmpSO->getMaterial().get())->rs();
}
//----- Rs setter
static void TW_CALL setASRsCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>(tmpSO->getMaterial(), v, 3);
    tmpSO->setMaterial(ashikhminShirleyMat);
}
//----- Rd getter
static void TW_CALL getASRdCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<ASM*>(tmpSO->getMaterial().get())->rd();
}
//----- Rd setter
static void TW_CALL setASRdCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<ASM> ashikhminShirleyMat = std::make_shared<ASM>(tmpSO->getMaterial(), v, 4);
    tmpSO->setMaterial(ashikhminShirleyMat);
}


//------------------------- CookTorrance
//----- Button to convert into CookTorrance
static void TW_CALL cTButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        // save old material properties
        oldMat = "Lambert";
        LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>
                (p->color());
        tmpSO->setMaterial(CookTorranceMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        oldMat = "Glass";
        GlassMaterial* p = (GlassMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>
                (p->color());
        tmpSO->setMaterial(CookTorranceMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        oldMat = "Phong";
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>
                (p->color(), p->diffuseCoeff(), p->specularity());
        tmpSO->setMaterial(CookTorranceMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        oldMat = "BlinnPhong";
        BPM* p = (BPM*)tmpSO->getMaterial().get();
        std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>
                (p->color(), p->diffuseCoeff(), p->specularity());
        tmpSO->setMaterial(CookTorranceMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        oldMat = "AshikhminShirley";
        ASM* p = (ASM*)tmpSO->getMaterial().get();
        std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>
                (p->color(), p->rd());
        tmpSO->setMaterial(CookTorranceMat);
    }
    else if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::WARD)
    {
        oldMat = "WARD";
        WardMaterial* p = (WardMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>(p->color(), p->diffuseCoeff());
        tmpSO->setMaterial(CookTorranceMat);
    }
    // re-init new variables
    antTBarReInit_material(oldMat, tmpSO, gBar, tmpSO->getName());
}
//----- DiffuseCoeff getter
static void TW_CALL getCTDiffuseCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<CTM*>(tmpSO->getMaterial().get())->diffuseCoeff();
}
//----- DiffuseCoeff setter
static void TW_CALL setCTDiffuseCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>(tmpSO->getMaterial(), v, 1);
    tmpSO->setMaterial(CookTorranceMat);
}
//----- FresnelFactor getter
static void TW_CALL getCTFressnelFactorCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<CTM*>(tmpSO->getMaterial().get())->fresnelFactor();
}
//----- SpecularCoeff setter
static void TW_CALL setCTFressnelFactorCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>(tmpSO->getMaterial(), v, 2);
    tmpSO->setMaterial(CookTorranceMat);
}
//----- Roughness getter
static void TW_CALL getCTRoughnessCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<CTM*>(tmpSO->getMaterial().get())->roughness();
}
//----- Roughness setter
static void TW_CALL setCTRoughnessCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>(tmpSO->getMaterial(), v, 3);
    tmpSO->setMaterial(CookTorranceMat);
}
//----- Reflectance getter
static void TW_CALL getCTReflectanceCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<CTM*>(tmpSO->getMaterial().get())->reflectance();
}
//----- Specularity setter
static void TW_CALL setCTReflectanceCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<CTM> CookTorranceMat = std::make_shared<CTM>(tmpSO->getMaterial(), v, 4);
    tmpSO->setMaterial(CookTorranceMat);
}


//------------------------- Ward
//----- Button to convert into Ward
static void TW_CALL wardButtonCB(void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    std::string oldMat;
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {
        // save old material properties
        oldMat = "Lambert";
        LambertMaterial* p = (LambertMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>
                (p->color());
        tmpSO->setMaterial(wardMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::PHONG)
    {
        oldMat = "Phong";
        PhongMaterial* p = (PhongMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>
                (p->color(), p->diffuseCoeff());
        tmpSO->setMaterial(wardMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        oldMat = "BlinnPhong";
        BPM* p = (BPM*)tmpSO->getMaterial().get();
        std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>
                (p->color(), p->diffuseCoeff());
        tmpSO->setMaterial(wardMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::GLASS)
    {
        oldMat = "Glass";
        GlassMaterial* p = (GlassMaterial*)tmpSO->getMaterial().get();
        std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>
                (p->color());
        tmpSO->setMaterial(wardMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        oldMat = "AshikhminShirley";
        ASM* p = (ASM*)tmpSO->getMaterial().get();
        std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>
                (p->color(), p->rd(), p->anisotropicFactorU(), p->anisotropicFactorV());
        tmpSO->setMaterial(wardMat);
    }
    if(tmpSO->getMaterial()->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        oldMat = "CookTorrance";
        CTM* p = (CTM*)tmpSO->getMaterial().get();
        std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>
                (p->color(), p->diffuseCoeff());
        tmpSO->setMaterial(wardMat);
    }
    // re-init new variables
    antTBarReInit_material(oldMat, tmpSO, gBar, tmpSO->getName());
}
//----- X getter
static void TW_CALL getWardXCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<WardMaterial*>(tmpSO->getMaterial().get())->x();
}
//----- X setter
static void TW_CALL setWardXCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>(tmpSO->getMaterial(), v, 1);
    tmpSO->setMaterial(wardMat);
}
//----- Y getter
static void TW_CALL getWardYCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<WardMaterial*>(tmpSO->getMaterial().get())->y();
}
//----- Anisotropic V setter
static void TW_CALL setWardYCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>(tmpSO->getMaterial(), v, 2);
    tmpSO->setMaterial(wardMat);
}
//----- diffuse coefficient getter
static void TW_CALL getWardDiffuseCoeffCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    *((float*) value) =  static_cast<WardMaterial*>(tmpSO->getMaterial().get())->diffuseCoeff();
}
//----- diffuse coefficient setter
static void TW_CALL setWardDiffuseCoeffCB(const void* value, void* clientData)
{
    SceneObject* tmpSO =  static_cast<SceneObject*>(clientData);
    float v = *((float*)value);
    std::shared_ptr<WardMaterial> wardMat = std::make_shared<WardMaterial>(tmpSO->getMaterial(), v, 3);
    tmpSO->setMaterial(wardMat);
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

        std::string nameBPButton = name;
        nameBPButton += " into BlinnPhong";
        const char* nameBPButtonC = nameBPButton.c_str();

        std::string nameGButton = name;
        nameGButton += " into Glass";
        const char* nameGButtonC = nameGButton.c_str();

        std::string nameASButton = name;
        nameASButton += " into AshikhminShirley";
        const char* nameASButtonC = nameASButton.c_str();

        std::string nameCTButton = name;
        nameCTButton += " into CookTorrance";
        const char* nameCTButtonC = nameCTButton.c_str();

        std::string nameWButton = name;
        nameWButton += " into Ward";
        const char* nameWButtonC = nameWButton.c_str();

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
            TwAddButton(bar, nameBPButtonC, bPButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameGButtonC, glassButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameASButtonC, aSButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameCTButtonC, cTButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameWButtonC, wardButtonCB, scene->getSceneObject(i).get(), grpNameC);

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
            TwAddButton(bar, nameBPButtonC, bPButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameGButtonC, glassButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameASButtonC, aSButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameCTButtonC, cTButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameWButtonC, wardButtonCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Variable for coeff props
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPhongAmbientCoeffCB, getPhongAmbientCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
            TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPhongDiffuseCoeffCB, getPhongDiffuseCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
            TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPhongSpecularCoeffCB, getPhongSpecularCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);

            // ATB Variable for shininess and specularity
            TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setPhongShininessCB, getPhongShininessCB, scene->getSceneObject(i).get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setPhongSpecularityCB, getPhongSpecularityCB, scene->getSceneObject(i).get(), grpNameFloat1C);
        }
        //---------------- Material is BlinnPhong
        else if(scene->getSceneObject(i)->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
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
            TwAddButton(bar, nameBPButtonC, PButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameGButtonC, glassButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameASButtonC, aSButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameCTButtonC, cTButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameWButtonC, wardButtonCB, scene->getSceneObject(i).get(), grpNameC);

            // ATB Variable for coeff props
            TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setBPAmbientCoeffCB, getBPAmbientCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
            TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setBPDiffuseCoeffCB, getBPDiffuseCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);
            TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setBPpecularCoeffCB, getBPSpecularCoeffCB, scene->getSceneObject(i).get(), grpNameFloat1C);

            // ATB Variable for shininess and specularity
            TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setBPShininessCB, getBPShininessCB, scene->getSceneObject(i).get(), grpNameFloatC);
            TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setBPSpecularityCB, getBPSpecularityCB, scene->getSceneObject(i).get(), grpNameFloat1C);
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
            TwAddButton(bar, nameBPButtonC, bPButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameASButtonC, aSButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameCTButtonC, cTButtonCB, scene->getSceneObject(i).get(), grpNameC);
            TwAddButton(bar, nameWButtonC, wardButtonCB, scene->getSceneObject(i).get(), grpNameC);

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

    std::string nameBPButton = objName;
    nameBPButton += " into BlinnPhong";
    const char* nameBPButtonC = nameBPButton.c_str();

    std::string nameGButton = objName;
    nameGButton += " into Glass";
    const char* nameGButtonC = nameGButton.c_str();

    std::string nameASButton = objName;
    nameASButton += " into AshikhminShirley";
    const char* nameASButtonC = nameASButton.c_str();

    std::string nameCTButton = objName;
    nameCTButton += " into CookTorrance";
    const char* nameCTButtonC = nameCTButton.c_str();

    std::string nameWButton = objName;
    nameWButton += " into Ward";
    const char* nameWButtonC = nameWButton.c_str();

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
        TwAddButton(bar, nameBPButtonC, bPButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameASButtonC, aSButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameCTButtonC, cTButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameWButtonC, wardButtonCB, scObj, grpNameC);
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
        TwAddButton(bar, nameBPButtonC, bPButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameASButtonC, aSButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameCTButtonC, cTButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameWButtonC, wardButtonCB, scObj, grpNameC);

        // ATB Variable for coeff props
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPhongAmbientCoeffCB, getPhongAmbientCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPhongDiffuseCoeffCB, getPhongDiffuseCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPhongSpecularCoeffCB, getPhongSpecularCoeffCB, scObj, grpNameFloat1C);

        // ATB Variable for shininess and specularity
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setPhongShininessCB, getPhongShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setPhongSpecularityCB, getPhongSpecularityCB, scObj, grpNameFloat1C);

    }
    //---------------- Material is BlinnPhong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
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
        TwAddButton(bar, namePButtonC, bPButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameASButtonC, aSButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameCTButtonC, cTButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameWButtonC, wardButtonCB, scObj, grpNameC);

        // ATB Variable for coeff props
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setBPAmbientCoeffCB, getBPAmbientCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setBPDiffuseCoeffCB, getBPDiffuseCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setBPSpecularCoeffCB, getBPSpecularCoeffCB, scObj, grpNameFloat1C);

        // ATB Variable for shininess and specularity
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setBPShininessCB, getPhongShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setBPSpecularityCB, getPhongSpecularityCB, scObj, grpNameFloat1C);

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
        TwAddButton(bar, nameBPButtonC, bPButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameASButtonC, aSButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameCTButtonC, cTButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameWButtonC, wardButtonCB, scObj, grpNameC);

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
    std::string nameLButton = objName;
    nameLButton += " into Lambert";
    const char* nameLButtonC = nameLButton.c_str();

    std::string namePButton = objName;
    namePButton += " into Phong";
    const char* namePButtonC = namePButton.c_str();

    std::string nameBPButton = objName;
    nameBPButton += " into BlinnPhong";
    const char* nameBPButtonC = nameBPButton.c_str();

    std::string nameGButton = objName;
    nameGButton += " into Glass";
    const char* nameGButtonC = nameGButton.c_str();

    std::string nameASButton = objName;
    nameASButton += " into AshikhminShirley";
    const char* nameASButtonC = nameASButton.c_str();

    std::string nameCTButton = objName;
    nameCTButton += " into CookTorrance";
    const char* nameCTButtonC = nameCTButton.c_str();

    std::string nameWButton = objName;
    nameWButton += " into Ward";
    const char* nameWButtonC = nameWButton.c_str();

    //----------------- Material is Lambert
    if(scObj->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT)
    {

        //---------- set name to specific variable
        std::string nameVar1 = objName + " Color";
        const char* nameVar1C = nameVar1.c_str();

        //---------- ATB variables
        // ATB Buttons to convert into another Material Type
        TwRemoveVar(bar, nameBPButtonC);
        TwRemoveVar(bar, namePButtonC);
        TwRemoveVar(bar, nameGButtonC);
        TwRemoveVar(bar, nameASButtonC);
        TwRemoveVar(bar, nameCTButtonC);
        TwRemoveVar(bar, nameWButtonC);

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
        TwRemoveVar(bar, nameBPButtonC);
        TwRemoveVar(bar, nameGButtonC);
        TwRemoveVar(bar, nameASButtonC);
        TwRemoveVar(bar, nameCTButtonC);
        TwRemoveVar(bar, nameWButtonC);

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
    //---------------- Material is BlinnPhong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
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
        TwRemoveVar(bar, namePButtonC);
        TwRemoveVar(bar, nameGButtonC);
        TwRemoveVar(bar, nameASButtonC);
        TwRemoveVar(bar, nameCTButtonC);
        TwRemoveVar(bar, nameWButtonC);

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
        TwRemoveVar(bar, nameBPButtonC);
        TwRemoveVar(bar, nameASButtonC);
        TwRemoveVar(bar, nameCTButtonC);
        TwRemoveVar(bar, nameWButtonC);
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
    std::string nameLButton = objName;
    nameLButton += " into Lambert";
    const char* nameLButtonC = nameLButton.c_str();

    std::string namePButton = objName;
    namePButton += " into Phong";
    const char* namePButtonC = namePButton.c_str();

    std::string nameBPButton = objName;
    nameBPButton += " into BlinnPhong";
    const char* nameBPButtonC = nameBPButton.c_str();

    std::string nameGButton = objName;
    nameGButton += " into Glass";
    const char* nameGButtonC = nameGButton.c_str();

    std::string nameASButton = objName;
    nameASButton += " into AshikhminShirley";
    const char* nameASButtonC = nameASButton.c_str();

    std::string nameCTButton = objName;
    nameCTButton += " into CookTorrance";
    const char* nameCTButtonC = nameCTButton.c_str();

    std::string nameWButton = objName;
    nameWButton += " into Ward";
    const char* nameWButtonC = nameWButton.c_str();

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
        TwRemoveVar(bar, nameBPButtonC);
        TwRemoveVar(bar, nameGButtonC);
        TwRemoveVar(bar, nameASButtonC);
        TwRemoveVar(bar, nameCTButtonC);
        TwRemoveVar(bar, nameWButtonC);
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
        TwRemoveVar(bar, nameBPButtonC);
        TwRemoveVar(bar, nameGButtonC);
        TwRemoveVar(bar, nameASButtonC);
        TwRemoveVar(bar, nameCTButtonC);
        TwRemoveVar(bar, nameWButtonC);

        // ATB Variable for coeff props
        TwRemoveVar(bar, nameVar2C);
        TwRemoveVar(bar, nameVar3C);
        TwRemoveVar(bar, nameVar4C);

        // ATB Variable for shininess and specularity
        TwRemoveVar(bar, nameVar5C);
        TwRemoveVar(bar, nameVar6C);

    }
    //---------------- Material was BlinnPhong
    else if(oldMat == "BlinnPhong")
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
        TwRemoveVar(bar, namePButtonC);
        TwRemoveVar(bar, nameGButtonC);
        TwRemoveVar(bar, nameASButtonC);
        TwRemoveVar(bar, nameCTButtonC);
        TwRemoveVar(bar, nameWButtonC);

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
        TwRemoveVar(bar, nameBPButtonC);
        TwRemoveVar(bar, nameASButtonC);
        TwRemoveVar(bar, nameCTButtonC);
        TwRemoveVar(bar, nameWButtonC);

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
        TwAddButton(bar, nameBPButtonC, bPButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameASButtonC, aSButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameCTButtonC, cTButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameWButtonC, wardButtonCB, scObj, grpNameC);
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
        TwAddButton(bar, nameBPButtonC, bPButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameASButtonC, aSButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameCTButtonC, cTButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameWButtonC, wardButtonCB, scObj, grpNameC);

        // ATB Variable for coeff props
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setPhongAmbientCoeffCB, getPhongAmbientCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setPhongDiffuseCoeffCB, getPhongDiffuseCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setPhongSpecularCoeffCB, getPhongSpecularCoeffCB, scObj, grpNameFloat1C);

        // ATB Variable for shininess and specularity
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setPhongShininessCB, getPhongShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setPhongSpecularityCB, getPhongSpecularityCB, scObj, grpNameFloat1C);
    }
    //---------------- Material is BlinnPhong
    else if(scObj->getMaterial()->getMaterialType() == BaseMaterial::BLINNPHONG)
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
        TwAddButton(bar, namePButtonC, PButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameGButtonC, glassButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameASButtonC, aSButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameCTButtonC, cTButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameWButtonC, wardButtonCB, scObj, grpNameC);

        // ATB Variable for coeff props
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setBPAmbientCoeffCB, getBPAmbientCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar3C, TW_TYPE_FLOAT, setBPDiffuseCoeffCB, getBPDiffuseCoeffCB, scObj, grpNameFloat1C);
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setBPSpecularCoeffCB, getBPSpecularCoeffCB, scObj, grpNameFloat1C);

        // ATB Variable for shininess and specularity
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setBPShininessCB, getBPShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar6C, TW_TYPE_FLOAT, setBPSpecularityCB, getBPSpecularityCB, scObj, grpNameFloat1C);
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
        TwAddButton(bar, nameBPButtonC, bPButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameASButtonC, aSButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameCTButtonC, cTButtonCB, scObj, grpNameC);
        TwAddButton(bar, nameWButtonC, wardButtonCB, scObj, grpNameC);

        // ATB Variable for refractiveIndex
        TwAddVarCB(bar, nameVar2C, TW_TYPE_FLOAT, setGlassRefractiveIdxCB, getGlassRefractiveIdxCB, scObj, grpNameFloat5C);

        // ATB Variable for shininess and specularCoefficient
        TwAddVarCB(bar, nameVar4C, TW_TYPE_FLOAT, setGlassShininessCB, getGlassShininessCB, scObj, grpNameFloatC);
        TwAddVarCB(bar, nameVar5C, TW_TYPE_FLOAT, setGlassSpecularCoeffCB, getGlassSpecularCoeffCB, scObj, grpNameFloat1C);
    }

}
