#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "material/baseMaterial.h"
#include "geometry/baseGeometry.h"
#include <memory>
#include <vector>

class SceneObject
{
private:
    std::shared_ptr<BaseGeometry>   mGeometry;
    std::shared_ptr<BaseMaterial>   mMaterial;
    std::string     mName;
    bool            mChanged;

public:
    SceneObject(const std::string &name,std::shared_ptr<BaseGeometry> geometry,std::shared_ptr<BaseMaterial> mat) : mGeometry(geometry),mMaterial(mat),mName(name),mChanged(false)
    {}
    std::shared_ptr<BaseGeometry>  getGeometry() const;
    std::shared_ptr<BaseMaterial>   getMaterial() const;
    std::string     getName() const;

    void            setMaterial(std::shared_ptr<BaseMaterial> material);
    void            setGeometry(std::shared_ptr<BaseGeometry> geometry);
    //check, if material changed
    bool            changed();

private:
    //called, after material has changed
    void            markAsChanged();
};

#endif //SCENEOBJECT_H
