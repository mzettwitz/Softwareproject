#include "../include/sceneobject.h"
#include "../include/material/lambertMaterial.h"
#include "../include/material/phongMaterial.h"
#include  "../include/structs.h"

BaseGeometry* SceneObject::getGeometry() const
{
    return mGeometry;
}

BaseMaterial* SceneObject::getMaterial() const
{
    return mMaterial;
}

std::string SceneObject::getName() const
{
    return mName;
}

void SceneObject::setMaterial(BaseMaterial *material)
{
    if(material->getMaterialType() != mMaterial->getMaterialType())
    {
        mMaterial = material;
        markAsChanged();
        return;
    }

    if(mMaterial->getMaterialType() == BaseMaterial::LAMBERT )
    {
        LambertMaterial* mat1 = dynamic_cast<LambertMaterial*>(mMaterial);
        LambertMaterial* mat2 = dynamic_cast<LambertMaterial*>(material);
        if(&mat1 != &mat2)
        {
            mMaterial = material;
            markAsChanged();
            return;
        }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::PHONG)
    {
        PhongMaterial* mat1 = dynamic_cast<PhongMaterial*>(mMaterial);
        PhongMaterial* mat2 = dynamic_cast<PhongMaterial*>(material);
        if(&mat1 != &mat2)
        {
            mMaterial = material;
            markAsChanged();
            return;
        }
    }
    else if(mMaterial->getMaterialType() == BaseMaterial::DISNEY)
    {
        /*DisneyMaterial* mat1 = dynamic_cast<DisneyMaterial*>(mMaterial);
         *DisneyMaterial* mat2 = dynmiac_cast<DisneyMaterial*>(material);
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
        /*GlassMaterial* mat1 = dynamic_cast<GlassMaterial*>(mMaterial);
         *GlassMaterial* mat2 = dynmiac_cast<GlassMaterial*>(material);
         * if(&mat1 != &mat2)
         * {
         *      mMaterial = material;
         *      markAsChanged();
         *      return;
         * }
         */
            //dummy
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

