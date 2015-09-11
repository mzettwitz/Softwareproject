#include "../../include/geometry/meshgroup.h"
#include "../../include/geometry/meshLoader.h"

using namespace optix;

void MeshGroup::load()
{
    if(!mFilename.empty())
    {
        std::cout << "loading obj : " << mFilename << std::endl;
        bool loaded = MeshLoader::loadOBJScene(mFilename.c_str(),mMesh);
        if(loaded)
        {
            std::cout << "loading successful." << std::endl;
        }
    }
}

std::shared_ptr<std::vector<std::shared_ptr<Mesh>>> MeshGroup::data()
{
    return mMesh;
}

std::shared_ptr<Mesh> MeshGroup::data(unsigned int i)
{
    if(i < mMesh->size())
    {
        return mMesh->at(i);
    }
    return nullptr;
}
