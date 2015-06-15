#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "baseMaterial.h"
#include "geometry/baseGeometry.h"

class SceneObject
{
private:
    BaseGeometry*   mGeometry;
    BaseMaterial*   mMaterial;
    std::string     mName;
    bool            mChanged;

public:
    SceneObject(const std::string &name,BaseGeometry *geometry,BaseMaterial *mat) : mGeometry(geometry),mMaterial(mat),mName(name),mChanged(false)
    {}

    BaseGeometry*   getGeometry() const;
    BaseMaterial*   getMaterial() const;
    std::string     getName() const;

    void            setMaterial(BaseMaterial *material);
    //check, if material changed
    bool            changed();

private:
    //called, after material has changed
    void            markAsChanged();
};

#endif //SCENEOBJECT_H
