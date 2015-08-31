#include "../include/sceneobject.h"
#include "../include/material/lambertMaterial.h"
#include "../include/material/phongMaterial.h"
#include "../include/material/glassMaterial.h"
#include "../include/material/disneyMaterial.h"
#include "../include/geometry/sphere.h"
#include "../include/geometry/mesh.h"
#include "../include/geometry/infinitePlane.h"
#include "../include/geometry/areaPlane.h"
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
            markMaterialAsChanged();
            return;
        }
    }
}

void SceneObject::setGeometry(std::shared_ptr<BaseGeometry> geometry)
{
    if(geometry->getGeometryType() != mGeometry->getGeometryType())
    {
        std::cout << mGeometry->getGeometryType() << std::endl;
        mGeometry = geometry;
        markGeometryAsChanged();
        return;
    }

    if(mGeometry->getGeometryType() == BaseGeometry::SPHERE )
    {
        std::shared_ptr<Sphere> geom1 = std::dynamic_pointer_cast<Sphere>(mGeometry);
        std::shared_ptr<Sphere> geom2 = std::dynamic_pointer_cast<Sphere>(geometry);
        if(&geom1 != &geom2)
        {
            mGeometry = geometry;
            markGeometryAsChanged();
            return;
        }
    }/*
    else if(mGeometry->getGeometryType() == BaseGeometry::MESH )
    {
        std::shared_ptr<Mesh> geom1 = std::dynamic_pointer_cast<Mesh>(mGeometry);
        std::shared_ptr<Mesh> geom2 = std::dynamic_pointer_cast<Mesh>(geometry);
        if(&geom1 != &geom2)
        {
            mGeometry = geometry;
            markGeometryAsChanged();
            return;
        }
    }*/
    else if(mGeometry->getGeometryType() == BaseGeometry::INFINITEPLANE )
    {
        std::shared_ptr<InfinitePlane> geom1 = std::dynamic_pointer_cast<InfinitePlane>(mGeometry);
        std::shared_ptr<InfinitePlane> geom2 = std::dynamic_pointer_cast<InfinitePlane>(geometry);
        if(&geom1 != &geom2)
        {
            mGeometry = geometry;
            markGeometryAsChanged();
            return;
        }
    }
    else if(mGeometry->getGeometryType() == BaseGeometry::AREAPLANE )
    {
        std::shared_ptr<AreaPlane> geom1 = std::dynamic_pointer_cast<AreaPlane>(mGeometry);
        std::shared_ptr<AreaPlane> geom2 = std::dynamic_pointer_cast<AreaPlane>(geometry);
        if(&geom1 != &geom2)
        {
            mGeometry = geometry;
            markGeometryAsChanged();
            return;
        }
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
