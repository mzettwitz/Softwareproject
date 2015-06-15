#include "../include/sceneobject.h"

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
    mMaterial = material;
    markAsChanged();
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

