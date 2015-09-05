#ifndef MESH_H
#define MESH_H

#include "baseGeometry.h"
#include "meshLoader.h"
using namespace optix;

class Mesh : public BaseGeometry
{
private:
    std::vector<float3> mVertices;
    float3* mVertex;
    std::vector<float2> mUVs;
    std::vector<float3> mNormals;
    std::vector<int3>   mVertexIndices;
    std::vector<int3>   mNormalIndices;
    std::vector<int3>   mUVIndices;
    std::string         mFilename;

    unsigned int mNumVertices;
    unsigned int mNumNormals;
    unsigned int mNumTextureCoordinates;
    unsigned int mNumPrimitives;

public:
    Mesh(std::string filename,float3 pos) : mFilename(filename), BaseGeometry(pos,"meshIntersectionProgram","meshBoundingBoxProgram","mesh.cu")
    {
        mGeometryType = MESH;
        if(!mFilename.empty())
        {
            std::cout << "loading obj : " << filename << std::endl;
            std::string file = std::string(sutilSamplesDir()) + "/sopro/assets/" + mFilename;
            bool loaded = MeshLoader::loadOBJ(file.c_str(),mVertices,mNormals,mUVs,mVertexIndices,mNormalIndices,mUVIndices,mNumPrimitives);
            mNumVertices = mVertices.size();
            mNumNormals = mNormals.size();
            mNumTextureCoordinates = mUVs.size();
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
