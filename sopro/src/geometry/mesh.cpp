#include "../../include/geometry/mesh.h"
#include "../../include/geometry/meshLoader.h"

using namespace optix;

Geometry Mesh::createGeometry(Context context) const
{
    Geometry geometry = context->createGeometry();
    geometry->setPrimitiveCount(mNumPrimitives);
    geometry->setBoundingBoxProgram(context->createProgramFromPTXFile(mPTXpath,mBoundingBoxProgram));
    geometry->setIntersectionProgram(context->createProgramFromPTXFile(mPTXpath,mIntersectionProgram));



    Buffer vertexBuffer = context->createBuffer(RT_BUFFER_INPUT,RT_FORMAT_FLOAT3,mVertices.size());
    float3* vertexData = static_cast<float3*>(vertexBuffer->map());
    std::copy(mVertices.begin(),mVertices.end(),vertexData);
    vertexBuffer->unmap();

    Buffer normalBuffer = context->createBuffer(RT_BUFFER_INPUT,RT_FORMAT_FLOAT3,mNormals.size());
    float3* normalData = static_cast<float3*>(normalBuffer->map());
    std::copy(mNormals.begin(),mNormals.end(),normalData);
    normalBuffer->unmap();

    Buffer uvBuffer = context->createBuffer(RT_BUFFER_INPUT,RT_FORMAT_FLOAT2,mUVs.size());
    float2* uvData = static_cast<float2*>(uvBuffer->map());
    std::copy(mUVs.begin(),mUVs.end(),uvData);
    uvBuffer->unmap();

    geometry["vertexBuffer"]->set(vertexBuffer);
    geometry["normalBuffer"]->set(normalBuffer);
    geometry["uvBuffer"]->set(uvBuffer);

    Buffer vertexIndexBuffer = context->createBuffer(RT_BUFFER_INPUT,RT_FORMAT_INT3,mVertexIndices.size());
    int3*   vertexIndexData = static_cast<int3*>(vertexIndexBuffer->map());
    std::copy(mVertexIndices.begin(),mVertexIndices.end(),vertexIndexData);
    vertexIndexBuffer->unmap();

    Buffer normalIndexBuffer = context->createBuffer(RT_BUFFER_INPUT,RT_FORMAT_INT3,mNormalIndices.size());
    int3* normalIndexData = static_cast<int3*>(normalIndexBuffer->map());
    std::copy(mNormalIndices.begin(),mNormalIndices.end(),normalIndexData);
    normalIndexBuffer->unmap();

    Buffer uvIndexBuffer = context->createBuffer(RT_BUFFER_INPUT,RT_FORMAT_INT3,mUVIndices.size());
    int3* uvIndexData = static_cast<int3*>(uvIndexBuffer->map());
    std::copy(mUVIndices.begin(),mUVIndices.end(),uvIndexData);
    uvIndexBuffer->unmap();

    geometry["vertexIndexBuffer"]->set(vertexIndexBuffer);
    geometry["normalIndexBuffer"]->set(normalIndexBuffer);
    geometry["uvIndexBuffer"]->set(uvIndexBuffer);

    geometry->markDirty();

    return geometry;
}

void Mesh::setFilename(const std::string &filename)
{
    mFilename = filename;
}

void Mesh::setObjectname(const std::string &objectname)
{
    mObjectname = objectname;
}

void Mesh::clear()
{
    mVertices.clear();
    mVertexIndices.clear();
    mNormals.clear();
    mNormalIndices.clear();
    mUVs.clear();
    mUVIndices.clear();
    mNumPrimitives = 0u;
}

void Mesh::setData(std::vector<float3> &v, std::vector<int3> &vI, std::vector<float3> &n, std::vector<int3> &nI, std::vector<float2> &uv, std::vector<int3> &uvI, unsigned int numPrimitives)
{
    mVertices = v;
    mVertexIndices = vI;
    mNormals = n;
    mNormalIndices = nI;
    mUVs = uv;
    mUVIndices = uvI;
    mNumPrimitives = numPrimitives;
}

void Mesh::load()
{
    if(!mFilename.empty())
    {
        std::cout << "loading obj : " << mFilename << std::endl;
        std::string file = std::string(sutilSamplesDir()) + "/sopro/assets/" + mFilename;
        bool loaded = MeshLoader::loadOBJ(file.c_str(),mVertices,mNormals,mUVs,mVertexIndices,mNormalIndices,mUVIndices,mNumPrimitives);
        if(loaded)
        {
            std::cout << "loading successful." << std::endl;
        }
    }
}

const std::string& Mesh::objectname() const
{
    return mObjectname;
}

std::string& Mesh::objectname()
{
    return mObjectname;
}
