#include "../../include/geometry/mesh.h"

using namespace optix;

Geometry Mesh::createGeometry(Context context) const
{
    Geometry geometry = context->createGeometry();
    return geometry;
}

void Mesh::setFilename(std::string filename)
{
    if(!filename.empty())
    {
        std::cout << "loading obj : " << filename << std::endl;
        std::string file = std::string(sutilSamplesDir()) + "/sopro/assets/" + mFilename;
        bool loaded = MeshLoader::loadOBJ(file.c_str(),mVertices,mNormals,mUVs);
        if(loaded)
        {
            std::cout << "loading successful." << std::endl;
        }
    }
}
