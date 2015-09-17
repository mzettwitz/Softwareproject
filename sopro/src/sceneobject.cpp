#include "../include/sceneobject.h"
#include "../include/material/lambertMaterial.h"
#include "../include/material/phongMaterial.h"
#include "../include/material/blinnPhongMaterial.h"
#include "../include/material/ashikhminShirleyMaterial.h"
#include "../include/material/glassMaterial.h"
#include "../include/material/cookTorranceMaterial.h"
#include "../include/material/wardMaterial.h"
#include "../include/material/disneyMaterial.h"
#include "../include/geometry/sphere.h"
#include "../include/geometry/mesh.h"
#include "../include/geometry/infinitePlane.h"
#include "../include/geometry/areaPlane.h"
#include "../include/structs.h"



std::shared_ptr<BaseGeometry> SceneObject::getGeometry() const
{
    return mGeometry;
}

std::shared_ptr<BaseMaterial> SceneObject::getMaterial() const
{
    return mMaterial;
}

std::string SceneObject::getName() const
{
    return mName;
}

void SceneObject::setMaterial(std::shared_ptr<BaseMaterial> material)
{
    if(material->getMaterialType() != mMaterial->getMaterialType())
    {
        std::cout << mMaterial->getMaterialType() << std::endl;
        mMaterial = material;
        markMaterialAsChanged();
        return;
    }

    if(mMaterial->getMaterialType() == BaseMaterial::LAMBERT )
    {
        std::shared_ptr<LambertMaterial> mat1 = std::dynamic_pointer_cast<LambertMaterial>(mMaterial);
        std::shared_ptr<LambertMaterial> mat2 = std::dynamic_pointer_cast<LambertMaterial>(material);
        if(&mat1 != &mat2)
        {
            mMaterial = material;
            markMaterialAsChanged();
            mMaterial->markTypeAsChanged();
            return;
        }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::PHONG)
    {
        std::shared_ptr<PhongMaterial> mat1 = std::dynamic_pointer_cast<PhongMaterial>(mMaterial);
        std::shared_ptr<PhongMaterial> mat2 = std::dynamic_pointer_cast<PhongMaterial>(material);
        if(&mat1 != &mat2)
        {
            mMaterial = material;
            markMaterialAsChanged();
            mMaterial->markTypeAsChanged();
            return;
        }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::BLINNPHONG)
    {
        std::shared_ptr<BlinnPhongMaterial> mat1 = std::dynamic_pointer_cast<BlinnPhongMaterial>(mMaterial);
         std::shared_ptr<BlinnPhongMaterial> mat2 = std::dynamic_pointer_cast<BlinnPhongMaterial>(material);
          if(&mat1 != &mat2)
          {
              mMaterial = material;
              markMaterialAsChanged();
              mMaterial->markTypeAsChanged();
              return;
         }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::GLASS)
    {
        std::shared_ptr<GlassMaterial> mat1 = std::dynamic_pointer_cast<GlassMaterial>(mMaterial);
        std::shared_ptr<GlassMaterial> mat2 = std::dynamic_pointer_cast<GlassMaterial>(material);
        if(&mat1 != &mat2)
        {
            mMaterial = material;
            markMaterialAsChanged();
            mMaterial->markTypeAsChanged();
            return;
        }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::ASHIKHMINSHIRLEY)
    {
        std::shared_ptr<AshikhminShirleyMaterial> mat1 = std::dynamic_pointer_cast<AshikhminShirleyMaterial>(mMaterial);
         std::shared_ptr<AshikhminShirleyMaterial> mat2 = std::dynamic_pointer_cast<AshikhminShirleyMaterial>(material);
          if(&mat1 != &mat2)
          {
               mMaterial = material;
               markMaterialAsChanged();
               mMaterial->markTypeAsChanged();
               return;
          }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::COOKTORRANCE)
    {
        std::shared_ptr<CookTorranceMaterial> mat1 = std::dynamic_pointer_cast<CookTorranceMaterial>(mMaterial);
        std::shared_ptr<CookTorranceMaterial> mat2 = std::dynamic_pointer_cast<CookTorranceMaterial>(material);
         if(&mat1 != &mat2)
          {
               mMaterial = material;
               markMaterialAsChanged();
               mMaterial->markTypeAsChanged();
               return;
          }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::WARD)
    {
        std::shared_ptr<WardMaterial> mat1 = std::dynamic_pointer_cast<WardMaterial>(mMaterial);
         std::shared_ptr<WardMaterial> mat2 = std::dynamic_pointer_cast<WardMaterial>(material);
          if(&mat1 != &mat2)
          {
               mMaterial = material;
               markMaterialAsChanged();
               mMaterial->markTypeAsChanged();
               return;
          }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::DISNEY)
    {
        /*std::shared_ptr<DisneyMaterial> mat1 = std::dynamic_pointer_cast<DisneyMaterial>(mMaterial);
         *std::shared_ptr<DisneyMaterial> mat2 = std::dynamic_pointer_cast<DisneyMaterial>(material);
         * if(&mat1 != &mat2)
         * {
         *      mMaterial = material;
         *      markMaterialAsChanged();
         *      mMaterial->markTypeAsChanged();
         *      return;
         * }
         */
            //dummy
    }
}

void SceneObject::updateGeometry()
{
    if(mGeometry->isChanged())
    {
        markGeometryAsChanged();
    }

}

bool SceneObject::isMaterialChanged()
{

   if(mMaterialChanged)
   {
       mMaterialChanged = false;
       return true;
   }
   return false;

}

bool SceneObject::isGeometryChanged()
{
    if(mGeometryChanged)
    {
        mGeometryChanged = false;
        return true;
    }
    return false;
}

void SceneObject::markMaterialAsChanged()
{
    mMaterialChanged = true;
}

void SceneObject::markGeometryAsChanged()
{
    mGeometryChanged = true;
}
