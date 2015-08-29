#include "../include/sceneobject.h"
#include "../include/material/lambertMaterial.h"
#include "../include/material/phongMaterial.h"
#include "../include/material/glassMaterial.h"
#include "../include/material/disneyMaterial.h"
#include  "../include/structs.h"



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
        markAsChanged();
        return;
    }

    if(mMaterial->getMaterialType() == BaseMaterial::LAMBERT )
    {
        std::shared_ptr<LambertMaterial> mat1 = std::dynamic_pointer_cast<LambertMaterial>(mMaterial);
        std::shared_ptr<LambertMaterial> mat2 = std::dynamic_pointer_cast<LambertMaterial>(material);
        if(&mat1 != &mat2)
        {
            mMaterial = material;
            markAsChanged();
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
            markAsChanged();
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
         *      markAsChanged();
         *      return;
         * }
         */
            //dummy
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::GLASS)
    {
        std::shared_ptr<GlassMaterial> mat1 = std::dynamic_pointer_cast<GlassMaterial>(mMaterial);
        std::shared_ptr<GlassMaterial> mat2 = std::dynamic_pointer_cast<GlassMaterial>(material);
        if(&mat1 != &mat2)
        {
            mMaterial = material;
            markAsChanged();
            return;
        }
    }
}

bool SceneObject::changed()
{

   if(mChanged)
   {
       mChanged = false;
       return true;
   }
   return false;

}

void SceneObject::markAsChanged()
{
    mChanged = true;
}
