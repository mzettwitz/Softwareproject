#ifndef MESH_H
#define MESH_H

#include "baseGeometry.h"
#include "meshLoader.h"
using namespace optix;

class Mesh : public BaseGeometry
{
private:
    std::vector<float3> mVertices;
    std::vector<float2> mUVs;
    std::vector<float3> mNormals;
    std::string         mFilename;

public:
    Mesh(std::string filename,float3 pos) : mFilename(filename), BaseGeometry(pos,"meshIntersectionProgram","meshBoundingBoxProgram","mesh.cu")
    {
        mGeometryType = MESH;
        if(!mFilename.empty())
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

    Geometry createGeometry(Context context) const;

    //Setter
    void setFilename(std::string filename);
    //Special getter for ATB
    const std::string& filename() const;
    std::string& filename();



};


#endif
