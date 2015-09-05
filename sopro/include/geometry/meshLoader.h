#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <optixu/optixpp_namespace.h>

using namespace optix;


class MeshLoader
{
public:
    static bool loadOBJ(const char* file, std::vector<float3>&outVertices,std::vector<float3> &outNormals,std::vector<float2> &outUVs,std::vector<int3> &outVertexIndices,std::vector<int3> &outNormalIndices,std::vector<int3> &outUVIndices,unsigned int &outNumPrimitives);

};




#endif
