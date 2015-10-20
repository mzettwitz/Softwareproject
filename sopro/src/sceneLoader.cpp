#include "../include/sceneLoader.h"
#include <iostream>
#include <stdio.h>
#include "../include/geometry/mesh.h"
#include <string.h>
#include "../include/material/lambertMaterial.h"
#include "../include/material/phongMaterial.h"
#include "../include/material/ashikhminShirleyMaterial.h"
#include "../include/material/blinnPhongMaterial.h"
#include "../include/material/cookTorranceMaterial.h"
#include "../include/material/wardMaterial.h"
#include "../include/material/disneyMaterial.h"
#include "../include/material/glassMaterial.h"
#include "../include/geometry/meshgroup.h"
#include <algorithm>

bool SceneLoader::loadScene(const std::string &filename, std::shared_ptr<Scene> scene,std::vector<float> &settings)
{
    std::string f = std::string(sutilSamplesDir()) + "/sopro/assets/" + filename;
    FILE * file = fopen(f.c_str(),"r");

    std::shared_ptr<MeshGroup> tempMeshGroup;
    std::vector<std::shared_ptr<BaseMaterial>> tempMaterials;
    unsigned int objectCount = 0;

    if(file == NULL)
    {
        std::cout << "Could NOT open file!" << std::endl;
    }
    while(true)
    {
        char lineHeader[128];
        int res = fscanf(file,"%s",lineHeader);
        if(res == EOF)
        {
            break;
        }
        //obj file
        if(strcmp(lineHeader,"s") == 0)
        {
            char objName[128];
            fscanf(file,"%s\n",objName);
            tempMeshGroup = std::make_shared<MeshGroup>(std::string(objName));
            tempMeshGroup->load();

        }
        //camera settings
        else if(strcmp(lineHeader,"c") == 0)
        {
            float3 pos;
            float3 dir;
            float3 rig;
            float2 angle;
            float fov;
            fscanf(file,"%f/%f/%f %f/%f/%f %f/%f/%f %f/%f/%f\n",&pos.x,&pos.y,&pos.z,&dir.x,&dir.y,&dir.z,&rig.x,&rig.y,&rig.z,&angle.x,&angle.y,&fov);
            settings.push_back(pos.x);
            settings.push_back(pos.y);
            settings.push_back(pos.z);
            settings.push_back(dir.x);
            settings.push_back(dir.y);
            settings.push_back(dir.z);
            settings.push_back(rig.x);
            settings.push_back(rig.y);
            settings.push_back(rig.z);
            settings.push_back(angle.x);
            settings.push_back(angle.y);
            settings.push_back(fov);
        }
        //dimensions
        else if(strcmp(lineHeader,"d") == 0)
        {
            float2 dim;
            fscanf(file,"%f/%f\n",&dim.x,&dim.y);
            settings.push_back(dim.x);
            settings.push_back(dim.y);
        }
        //lights
        else if(strcmp(lineHeader,"l") == 0)
        {
            float3 pos;
            float3 color;
            float intensity;

            fscanf(file,"%f/%f/%f %f/%f/%f %f\n",&pos.x,&pos.y,&pos.z,&color.x,&color.y,&color.z,&intensity);
            PointLight l;
            l.padding = 0u;
            l.position = pos;
            l.color = color;
            l.intensity = intensity;
            scene->addLight(l);
        }
        //object coordinates
        else if(strcmp(lineHeader,"o") == 0)
        {
            float3 pos;
            float4 rot;
            float3 scale;
            BaseGeometry::GeometryType type;
            fscanf(file,"%d %f/%f/%f %f/%f/%f/%f %f/%f/%f\n",&type,&pos.x,&pos.y,&pos.z,&rot.x,&rot.y,&rot.z,&rot.w,&scale.x,&scale.y,&scale.z);
            if(type == BaseGeometry::MESH)
            {
                tempMeshGroup->data(objectCount)->setPosition(pos);
                tempMeshGroup->data(objectCount)->setRotation(rot);
                tempMeshGroup->data(objectCount)->setScale(scale);
            }
            else if(type == BaseGeometry::SPHERE)
            {
                    //Later,...
            }
            objectCount++;
        }
        //materials
        else if(strcmp(lineHeader,"m") == 0)
        {
            BaseMaterial::MaterialType type;
            fscanf(file,"%d",&type);
            switch(type)
            {
            case BaseMaterial::LAMBERT :
            {
                float3 color;
                fscanf(file,"%f/%f/%f\n",&color.x,&color.y,&color.z);
                LambertMaterial m(color);
                std::shared_ptr<LambertMaterial> mp = std::make_shared<LambertMaterial>(m);
                tempMaterials.push_back(mp);
                break;
            }
            case BaseMaterial::PHONG :
            {
                float3 color;
                float diff;
                float spec;
                float amb;
                float shine;
                float refl;
                fscanf(file,"%f/%f/%f %f/%f %f/%f/%f\n",&color.x,&color.y,&color.z,&diff,&spec,&amb,&shine,&refl);
                PhongMaterial m(color,amb,diff,spec,shine,refl);
                std::shared_ptr<PhongMaterial> mp = std::make_shared<PhongMaterial>(m);
                tempMaterials.push_back(mp);
                break;
            }
            case BaseMaterial::BLINNPHONG :
            {
                float3 color;
                float diff;
                float spec;
                float amb;
                float shine;
                float refl;
                fscanf(file,"%f/%f/%f %f/%f %f/%f/%f\n",&color.x,&color.y,&color.z,&diff,&spec,&amb,&shine,&refl);
                BlinnPhongMaterial m(color,amb,diff,spec,shine,refl);
                std::shared_ptr<BlinnPhongMaterial> mp = std::make_shared<BlinnPhongMaterial>(m);
                tempMaterials.push_back(mp);
                break;
            }
            case BaseMaterial::ASHIKHMINSHIRLEY :
            {
                float3 color;
                float diff;
                float spec;
                float u;
                float v;
                fscanf(file,"%f/%f/%f %f/%f %f/%f\n",&color.x,&color.y,&color.z,&diff,&spec,&u,&v);
                AshikhminShirleyMaterial m(color,u,v,spec,diff);
                std::shared_ptr<AshikhminShirleyMaterial> mp = std::make_shared<AshikhminShirleyMaterial>(m);
                tempMaterials.push_back(mp);
                break;
            }
            case BaseMaterial::COOKTORRANCE :
            {
                float3 color;
                float diff;
                float spec;
                float fresnel;
                float rough;
                float refl;
                fscanf(file,"%f/%f/%f %f/%f %f/%f/%f\n",&color.x,&color.y,&color.z,&diff,&spec,&fresnel,&rough,&refl);
                CookTorranceMaterial m(color,diff,spec,fresnel,rough,refl);
                std::shared_ptr<CookTorranceMaterial> mp = std::make_shared<CookTorranceMaterial>(m);
                tempMaterials.push_back(mp);
                break;
            }
            case BaseMaterial::GLASS :
            {
                float3 color;
                float spec;
                float rIdx;
                float shine;
                fscanf(file,"%f/%f/%f %f/%f/%f\n",&color.x,&color.y,&color.z,&spec,&rIdx,&shine);
                GlassMaterial m(color,rIdx,shine,spec);
                std::shared_ptr<GlassMaterial> mp = std::make_shared<GlassMaterial>(m);
                tempMaterials.push_back(mp);
                break;
            }
            case BaseMaterial::WARD :
            {
                float3 color;
                float diff;
                float spec;
                float u;
                float v;
                fscanf(file,"%f/%f/%f %f/%f %f/%f\n",&color.x,&color.y,&color.z,&diff,&spec,&u,&v);
                WardMaterial m(color,diff,spec,u,v);
                std::shared_ptr<WardMaterial> mp = std::make_shared<WardMaterial>(mp);
                tempMaterials.push_back(mp);
                break;
            }
            case BaseMaterial::DISNEY :
            {
                break;
            }
            }
        }
    }

    std::cout << "loading successful. start processing." << std::endl;
    //process data


    for(unsigned int i = 0;i < tempMeshGroup->data()->size();++i)
    {
        std::shared_ptr<SceneObject> sc = std::make_shared<SceneObject>(tempMeshGroup->data(i)->objectname(),tempMeshGroup->data(i),tempMaterials.at(i));

         scene->addSceneObject(sc);
    }
    fclose(file);
    return true;
}

bool SceneLoader::saveScene(const std::string &filename, std::shared_ptr<Scene> scene,std::vector<float> &settings)
{
    std::string f = std::string(sutilSamplesDir()) + "/sopro/assets/" + filename + ".ssf";
    FILE * file = fopen(f.c_str(),"w");


    //save obj

    //get meshname
    std::string objName;
    for(unsigned int i = 0;i < scene->getSceneObjectCount();++i)
    {
        if(scene->getSceneObject(i)->getGeometry()->getGeometryType() == BaseGeometry::MESH)
        {
            objName = std::dynamic_pointer_cast<Mesh>(scene->getSceneObject(i)->getGeometry())->filename();
            break;
        }
        else
        {
            std::cout<< "Could not save file, due to our little parser" << std::endl;
            return false;
        }
    }
    std::fprintf(file,"#objfilename\n");
    std::fprintf(file,"s %s\n",objName.c_str());

    //save settings
    //width, height, cpos, cdir,cright,horAngle,vertAngle,FOV,title,

    fprintf(file,"#settings\n");
    //camera pos, direction, right, horAngle, vertAngle,FOV
    fprintf(file,"c %f/%f/%f %f/%f/%f %f/%f/%f %f/%f/%f\n",settings.at(0),settings.at(1),settings.at(2),settings.at(3),settings.at(4),settings.at(5),settings.at(6),settings.at(7),settings.at(8),settings.at(9),settings.at(10),settings.at(11));
    //width height
    fprintf(file,"d %f/%f\n",settings.at(12),settings.at(13));
    //save lights
    float3 position = make_float3(0,0,0);
    float3 color = make_float3(0,0,0);
    fprintf(file,"#lights\n");
    float intensity = 0;
    for(unsigned int i = 0;i < scene->getLightCount();++i)
    {
        position = scene->getLight(i).position;
        color = scene->getLight(i).color;
        intensity = scene->getLight(i).intensity;

        fprintf(file,"l %f/%f/%f %f/%f/%f %f\n",position.x,position.y,position.z,color.x,color.y,color.z,intensity);
    }
    //save objects
    float4 rotation = make_float4(0,0,0,0);
    float3 scale = make_float3(0,0,0);
    fprintf(file,"#objects\n");


    for(unsigned int i = 0;i < scene->getSceneObjectCount();++i)
    {
        position = scene->getSceneObject(i)->getGeometry()->position();
        rotation = scene->getSceneObject(i)->getGeometry()->rotation();
        scale = scene->getSceneObject(i)->getGeometry()->scale();

        fprintf(file,"o %d %f/%f/%f %f/%f/%f/%f %f/%f/%f\n",scene->getSceneObject(i)->getGeometry()->getGeometryType(),position.x,position.y,position.z,rotation.x,rotation.y,rotation.z,rotation.w,scale.x,scale.y,scale.z);
    }
    //save materials
    fprintf(file,"#materials\n");
    for(unsigned int i = 0;i < scene->getSceneObjectCount();++i)
    {
        std::shared_ptr<BaseMaterial> mat = scene->getSceneObject(i)->getMaterial();
        switch(mat->getMaterialType())
        {
        case BaseMaterial::LAMBERT :
        {
            color = std::dynamic_pointer_cast<LambertMaterial>(mat)->color();

            fprintf(file,"m %d %f/%f/%f\n",BaseMaterial::LAMBERT,color.x,color.y,color.z);
            break;
        }
        case BaseMaterial::PHONG :
        {
            std::shared_ptr<PhongMaterial> ph = std::dynamic_pointer_cast<PhongMaterial>(mat);
            color = ph->color();
            float diff = ph->diffuseCoeff();
            float spec = ph->specularCoeff();
            float amb = ph->ambientCoeff();
            float shine = ph->shininess();
            float refl = ph->specularity();
            fprintf(file,"m %d %f/%f/%f %f/%f %f/%f/%f\n",BaseMaterial::PHONG,color.x,color.y,color.z,diff,spec,amb,shine,refl);
            break;
        }
        case BaseMaterial::BLINNPHONG :
        {
            std::shared_ptr<BlinnPhongMaterial> bl = std::dynamic_pointer_cast<BlinnPhongMaterial>(mat);
            color = bl->color();
            float diff = bl->diffuseCoeff();
            float spec = bl->specularCoeff();
            float amb = bl->ambientCoeff();
            float shine = bl->shininess();
            float refl = bl->specularity();
            fprintf(file,"m %d %f/%f/%f %f/%f %f/%f/%f\n",BaseMaterial::BLINNPHONG,color.x,color.y,color.z,diff,spec,amb,shine,refl);
            break;
        }
        case BaseMaterial::COOKTORRANCE :
        {
            std::shared_ptr<CookTorranceMaterial> c = std::dynamic_pointer_cast<CookTorranceMaterial>(mat);
            color = c->color();
            float diff = c->diffuseCoeff();
            float spec = c->specularCoeff();
            float f = c->fresnelFactor();
            float r = c->roughness();
            float refl = c->reflectance();
            fprintf(file,"m %d %f/%f/%f %f/%f %f/%f/%f\n",BaseMaterial::COOKTORRANCE,color.x,color.y,color.z,diff,spec,f,r,refl);
            break;
        }
        case BaseMaterial::ASHIKHMINSHIRLEY :
        {
            std::shared_ptr<AshikhminShirleyMaterial> a = std::dynamic_pointer_cast<AshikhminShirleyMaterial>(mat);
            color = a->color();
            float diff = a->diffuseCoeff();
            float spec = a->specularCoeff();
            float u = a->anisotropicFactorU();
            float v = a->anisotropicFactorV();
            fprintf(file,"m %d %f/%f/%f %f/%f %f/%f\n",BaseMaterial::ASHIKHMINSHIRLEY,color.x,color.y,color.z,diff,spec,u,v);
            break;
        }
        case BaseMaterial::GLASS :
        {
            std::shared_ptr<GlassMaterial> g = std::dynamic_pointer_cast<GlassMaterial>(mat);
            color = g->color();
            float spec = g->specularCoeff();
            float rIdx = g->refractiveIdx();
            float shine =g->shininess();

            fprintf(file,"m %d %f/%f/%f %f/%f/%f\n",BaseMaterial::GLASS,color.x,color.y,color.z,spec,rIdx,shine);
            break;
        }
        case BaseMaterial::WARD :
        {
            std::shared_ptr<WardMaterial> w = std::dynamic_pointer_cast<WardMaterial>(mat);
            color = w->color();
            float diff = w->diffuseCoeff();
            float spec = w->specularCoeff();
            float u = w->anisotropicFactorU();
            float v = w->anisotropicFactorV();
            fprintf(file,"m %d %f/%f/%f %f/%f %f/%f\n",BaseMaterial::WARD,color.x,color.y,color.z,diff,spec,u,v);
            break;
        }
        case BaseMaterial::DISNEY :
            std::shared_ptr<DisneyMaterial> d = std::dynamic_pointer_cast<DisneyMaterial>(mat);
            // TODO
            break;
        }

    }
    fclose(file);
    return true;
}
