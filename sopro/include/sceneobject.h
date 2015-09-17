#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "material/baseMaterial.h"
#include "geometry/baseGeometry.h"
#include "geometry/mesh.h"
#include <memory>
#include <vector>

class SceneObject
{
private:
    std::shared_ptr<BaseGeometry>   mGeometry;
    std::shared_ptr<BaseMaterial>   mMaterial;
    std::string     mName;
    bool            mMaterialChanged;
    bool            mGeometryChanged;

public:
    SceneObject(const std::string &name,std::shared_ptr<BaseGeometry> geometry,std::shared_ptr<BaseMaterial> mat) : mGeometry(geometry),mMaterial(mat),mName(name),mMaterialChanged(false),mGeometryChanged(false)
    {}
    std::shared_ptr<BaseGeometry>  getGeometry() const;
    std::shared_ptr<BaseMaterial>   getMaterial() const;
    std::string     getName() const;

    void            setMaterial(std::shared_ptr<BaseMaterial> material);
    void            setGeometry(std::shared_ptr<BaseGeometry> geometry);
    void            updateGeometry();
    //check, if material changed
    bool            isMaterialChanged();
    bool            isGeometryChanged();

private:
    //called, after material has changed
    void            markMaterialAsChanged();
    void            markGeometryAsChanged();

    //only for meshes!!!
    bool operator <(const std::shared_ptr<SceneObject> so) const
    {
        return strcmp(std::dynamic_pointer_cast<Mesh>(mGeometry)->objectname().c_str(),std::dynamic_pointer_cast<Mesh>(so->getGeometry())->objectname().c_str()) < 0;
    }
};

#endif //SCENEOBJECT_H
