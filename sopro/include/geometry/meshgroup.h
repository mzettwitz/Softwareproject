#ifndef MESHGROUP_H
#define MESHGROUP_H

#include <vector>
#include <string>
#include "mesh.h"

class MeshGroup
{
private:
    std::shared_ptr<std::vector<std::shared_ptr<Mesh>>> mMesh;
    std::string mFilename;
public:
    MeshGroup(std::string filename) : mFilename(filename)
    {
        mMesh = std::make_shared<std::vector<std::shared_ptr<Mesh>>>();
    }

    void load();
    std::shared_ptr<std::vector<std::shared_ptr<Mesh>>> data();
    std::shared_ptr<Mesh> data(unsigned int i);
};




#endif
