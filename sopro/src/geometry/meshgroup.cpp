#include "../../include/geometry/meshgroup.h"
#include "../../include/geometry/meshLoader.h"

using namespace optix;

void MeshGroup::load()
{
    if(!mFilename.empty())
    {
        std::cout << "loading obj : " << mFilename << std::endl;
        std::string file = std::string(sutilSamplesDir()) + "/sopro/assets/" + mFilename;
        bool loaded = MeshLoader::loadOBJScene(file.c_str(),mMesh);
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
