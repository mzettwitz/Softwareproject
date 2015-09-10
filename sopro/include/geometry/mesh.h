#ifndef MESH_H
#define MESH_H

#include "baseGeometry.h"
using namespace optix;



class Mesh : public BaseGeometry
{
private:
    std::vector<float3> mVertices;
    std::vector<float2> mUVs;
    std::vector<float3> mNormals;
    std::vector<int3>   mVertexIndices;
    std::vector<int3>   mNormalIndices;
    std::vector<int3>   mUVIndices;
    std::string         mFilename;
    std::string         mObjectname;

    unsigned int mNumPrimitives;

public:
    Mesh(std::string filename,float3 pos) : mFilename(filename), BaseGeometry(pos,"meshIntersectionProgram","meshBoundingBoxProgram","mesh.cu")
    {
        mGeometryType = MESH;
    }

    Geometry    createGeometry(Context context) const;
    void        clear();
    void        load();

    //Setter
    void setFilename(const std::string &filename);
    //Special getter for ATB
    const std::string& filename() const;
    std::string& filename();

    void setObjectname(const std::string &objectname);

    const std::string& objectname() const;
    std::string& objectname();

    void setData(std::vector<float3> &v,std::vector<int3> &vI,std::vector<float3> &n,std::vector<int3> &nI,std::vector<float2> &uv,std::vector<int3> &uvI,unsigned int numPrimitives);
};


#endif
