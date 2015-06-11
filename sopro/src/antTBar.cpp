#include "../include/antTBar.h"

// States
bool phongState = false;
bool disneyState = false;
bool glasState = false; // evtl array mit states für jedes objekt übergeben

void antTBar(int &width, int &height, std::vector<Material> &mat, Context &context)
{
    // Init ATB
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(width, height);

    // Create ATB
    TwBar *matBar = TwNewBar("MaterialEditor");
    TwDefine(" MaterialEditor size='200 400' color='118 185 0' alpha=160");

    // Test purposes
    for(int i = 0; i < mat.size(); i++)
    {
        const char* name = "colorProps " + (char)i;

        // Color
        float fColor[] = {0.f,0.f,0.f};

        TwAddVarRW(matBar, name, TW_TYPE_COLOR3F, fColor, " group='BasicMaterial' "); // evtl string am Ende selber schreiben mit i
        
        float3 f3Color = fTof3(fColor);
        plainColorMaterial newMat(f3Color,"plainColorMaterial.cu");
        mat[i] = (newMat.createMaterial(context));	//overwrite specific material in vector
    }


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
    TwDraw();
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

float3 fTof3(float f[3]){
    return float3{f[0], f[1], f[2]};
}
