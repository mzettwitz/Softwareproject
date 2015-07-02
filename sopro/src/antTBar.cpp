#include "../include/antTBar.h"

// States
bool phongState = false;
bool disneyState = false;
bool glasState = false; // evtl array mit states für jedes objekt übergeben


// Callbacks
// Lambert
static void TW_CALL getLambertCB(void* value, void* clientData)
{
    SceneObject* tmpSO =  ((SceneObject*) clientData);
    *((float3*) value) =  ((LambertMaterial*) tmpSO->getMaterial().get())->color();
}
static void TW_CALL setLambertCB(const void* value, void* clientData)
{
   SceneObject* tmpSO =  ((SceneObject*) clientData);
   ((LambertMaterial*) tmpSO->getMaterial().get())->setColor(*((float3*)value));
   tmpSO->markAsChanged();
}

// Phong



// Variable init
void antTBar(std::shared_ptr<Scene> scene, TwBar *bar)
{
    // DUMMY FOR ENUM
/*
    // Define enum type to pick the material type
    TwEnumVal shadeEV[] = // array used to describe the material type
    {
        { BaseMaterial::LAMBERT,"Lambert"   },
        { BaseMaterial::PHONG,  "Phong"     },
        { BaseMaterial::DISNEY, "Disney"    },
        { BaseMaterial::GLASS,  "Glass"     }
    };
    TwType shadeMode = TwDefineEnum("ShadeMode", shadeEV, 4);

    // Define structs to describe the material properties of each material type
    // Lambert
    TwStructMember lambertMembers[] = // array used to describe tweakable variables of the Lambert structure
    {
        //{ "Mode",   shadeMode, offsetof(BaseMaterial, BaseMaterial::mMaterialType),    " help='Shading mode' " },
        { "Color",  TW_TYPE_COLOR3F, offsetof(LambertMaterial, LambertMaterial::mColor),     " help='Diffuse Lambert color' " }
    };
    TwType lambertType = TwDefineStruct("Lambert", lambertMembers, 1, sizeof(LambertMaterial), NULL, NULL);

*/
    for(int i = 0; i < scene->getSceneObjectCount(); i++)
    {
        const char* name = scene->getSceneObject(i)->getName().c_str();

        if(scene->getSceneObject(i)->getMaterial()->getMaterialType() == BaseMaterial::LAMBERT){
            //std::shared_ptr<LambertMaterial> objMat = std::dynamic_pointer_cast<LambertMaterial>(scene->getSceneObject(i)->getMaterial());
            //TwAddVarCB(bar, name, lambertType, LambertMaterial::setLambertColorCB(),LambertMaterial::getLambertColorCB(),objMat, NULL);
            TwAddVarCB(bar, name, TW_TYPE_COLOR3F, setLambertCB, getLambertCB, scene->getSceneObject(i).get(), " group='Lambert Objects' ");
        }
    }

    // Test purposes
    /*
    std::shared_ptr<SceneObject> obj = scene->getSceneObject(0);
    const char* name = obj->getName().c_str();

    //delete scene->getSceneObject(i)->getMaterial();

    // Color
    float fColor[3];
    std::shared_ptr<LambertMaterial> objMat = std::dynamic_pointer_cast<LambertMaterial>(obj->getMaterial());
    if(scene->getSceneObject(0)->getMaterial()->getMaterialType() == 1)
    {
        fColor[0] = objMat->color().x;
        fColor[1] = objMat->color().y;
        fColor[2] = objMat->color().z;
    }

    TwAddVarRW(bar, name, TW_TYPE_COLOR3F, fColor, " group='BasicMaterial' ");
    objMat->setColor(make_float3(fColor[0], fColor[1], fColor[2]));
    std::shared_ptr<LambertMaterial> lamMat = std::make_shared<LambertMaterial>(make_float3(fColor[0], fColor[1], fColor[2]));
    scene->getSceneObject(0)->setMaterial(lamMat);
*/


    //callback from ATB
    //get all objects in Scene
    /* something like this
     *
     * drawTWbar()
     * {
     *     //dropdownmenu
     *        for(int i = 0;i < mScene->getSceneObjects().size();++i)
     *          {
     *              mScene->getSceneObject(i)->getName();
     *              add to dropdownmenu;
     *          }
     *     //parameters
     *          unsigned int index = dropdownmenu.selected().index;
     *
     *          BaseMaterial::MaterialType matType= mScene->getSceneObject(i)->getMaterial()->getMaterialType();
     *          BaseGeometry::GeometryType geomType= mScene->getSceneObject(i)->getGeometry()->getGeometryType();
     *
     * switch...
     *
     *
     * setMaterial
     * }
     *
     *
     *
     */



    /*
    for(i = 0; i < mat.size; i++)
        {

            // different shading options
            TwAddVarCB(matBar, "Phong Shading", TW_TYPE_BOOLCPP, setPhong, getPhong, NULL, "group='Shading' "); // after "...Shading key = p"
            TwAddVarCB(matBar, "Disney Shading", TW_TYPE_BOOLCPP, setDisney, getDisney, NULL, "group='Shading' "); // after "...Shading key = d"
            TwAddVarCB(matBar, "Glas", TW_TYPE_BOOLCPP, setGlas, getGlas, NULL, "group='Shading' "); // after "...Shading key = d"

        if(getGlas)
        {
            name = "glasProps " + std::to_string(i);

            // refractive index + color
            float n = 1.f;
            float fColor[] = {0.f,0.f,0.f};

            TwAddVarRW(matBar, name, TW_TYPE_COLOR3F, fColor, " group='GlasMaterial' ");

            float3 f3Color = fTof3(fColor);
            glasMaterial newMat(f3Color, n);
            mat[i] = newMat;	//overwrite specific material in vector
        }
        else if(getPhong)
        {
            nameA = "Ambient " + std::to_string(i);
            nameD = "Diffuse " + std::to_string(i);
            nameS = "Specular " + std::to_string(i);

            // ambient, duffuse, specular
            float fAmbientColor[] = {0.f,0.f,0.f};
            float fDiffuseColor[] = {0.f,0.f,0.f};
            float fSpecularColor[] = {0.f,0.f,0.f};

            TwAddVarRW(matBar, nameA, TW_TYPE_COLOR3F, fAmbientColor, " group='PhongMaterial' ");
            TwAddVarRW(matBar, nameD, TW_TYPE_COLOR3F, fDiffuseColor, " group='PhongMaterial' ");
            TwAddVarRW(matBar, nameS, TW_TYPE_COLOR3F, fSpecularColor, " group='PhongMaterial' ");

            float3 f3AmbientColor = fTof3(fAmbientColor);
            float3 f3DiffuseColor = fTof3(fDiffuseColor);
            float3 f3SpecularColor = fTof3(fSpecularColor);
            glasMaterial newMat(f3AmbientColor, f3DiffuseColor, f3SpecularColor);
            mat[i] = newMat;	//overwrite specific material in vector
        }
        else if(getDisney)
        {
            ////////////////DUMMY//////////
            name = "colorProps " + std::to_string(i);

            // Color
            float fColor[] = {0.f,0.f,0.f};

            TwAddVarRW(matBar, name, TW_TYPE_COLOR3F, fColor, " group='BasicMaterial' "); // evtl string am Ende selber schreiben mit i

            float3 f3Color = fTof3(fColor);
            plainColorMaterial newMat(f3Color);
            mat[i] = newMat;	//overwrite specific material in vector
        }
        else
        {
            //plainColor
            name = "colorProps " + std::to_string(i);

            // Color
            float fColor[] = {0.f,0.f,0.f};

            TwAddVarRW(matBar, name, TW_TYPE_COLOR3F, fColor, " group='BasicMaterial' "); // evtl string am Ende selber schreiben mit i

            float3 f3Color = fTof3(fColor);
            plainColorMaterial newMat(f3Color);
            mat[i] = newMat;	//overwrite specific material in vector
        }



        }
            // IDEA: different shading options for each object

    */
}




/*

        // Phong Shading
        // Callback function called by AntTweakBar to enable/disable Phong Shading
        void TW_CALL setPhong(const void *value, void *  /*clientData/) // need another *
        {
            phongState = *static_cast<const bool *>(value);
        }

        // Callback function called by AntTweakBar to get Phong Shading State
        void TW_CALL getPhong(void *value, void * /*clientData/)
        {
            *static_cast<bool *>(value) = phongState;
        }



        //Disney BRDF
        // Callback function called by AntTweakBar to enable/disable Disney BRDF
        void TW_CALL setDisney(const void *value, void * /*clientData/)
        {
            disneyState = *static_cast<const bool *>(value);
        }

        // Callback function called by AntTweakBar to get Disney BRDF State
        void TW_CALL getDisney(void *value, void * /*clientData/)
        {
            *static_cast<bool *>(value) = disneyState;
        }


        // Glas
        // Callback function called by AntTweakBar to enable/disable glas
        void TW_CALL setGlas(const void *value, void * /*clientData/)
        {
            glasState = *static_cast<const bool *>(value);
        }

        // Callback function called by AntTweakBar to get glas State
        void TW_CALL getGlas(void *value, void * /*clientData/)
        {
            *static_cast<bool *>(value) = glasState;
        }
*/


